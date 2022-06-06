#include <Renderer.h>
#include <Core/Window.h>
#include <Core/Object.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

sol::Mat4f projection;
sol::Mat4f view;
sol::Mat4f model;

// Simple scene setup function
static void LoadScene(Renderer* renderer);
// ImGui UI functions
static void ImGuiObjectControlMenu(ObjectHandler& handler, bool* objectCreation);
static void ImGuiCurrentObjectMenu(ObjectHandler& handler, int currentIndex);
static void ImGuiMaterialControlMenu(ObjectHandler& handler, bool* materialCreation);
static void ImGuiObjectCreationMenu(ObjectHandler& handler, bool* objectCreation);
static void ImGuiMaterialCreationMenu(ObjectHandler& handler, bool* materialCreation);
static void ImGuiCursorInfoMenu(ObjectHandler& handler, const sol::Vec2f cursorPos);

// Overall data
Renderer::Renderer(Window* const window, size_t vertices)
: m_Window(window), m_Camera(window->AspectRatio()), m_Vertices(vertices), m_ObjectHandler(std::make_unique<ObjectHandler>())
{
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize OpenGL bindings");
	}

	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(this->m_VAO);

	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->m_Vertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// Just for logging purposes, log the amount of allocated bytes
	// It should be equal to this->m_Vertices * sizeof(Vertex)
	int size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	std::cout << "VBO max vertex count: " << size << " bytes of memory\n";
	if (size != this->m_Vertices * sizeof(Vertex))
	{
		throw std::runtime_error("Vertex Buffer Object wasn't initialized correctly");
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ObjectHandler& handler = this->GetObjectHandler();

	::LoadScene(this);

	Object quad = Object
	({
		Vertex(-3.0f, 3.0f, sol::Vec4f(1.0f)),
		Vertex(3.0f, 3.0f, sol::Vec4f(1.0f)),
		Vertex(3.0f, -3.0f, sol::Vec4f(1.0f)),
		Vertex(-3.0f, -3.0f, sol::Vec4f(1.0f)),
	}, handler.FindMaterial("Basic_Material"));

	quad.CreateAABB();
	handler.AddObject(std::move(quad));

	Camera& cam = this->GetCamera();
 	cam.fov = 45.0f;
 	cam.position = sol::Vec3f(0.0f, 0.0f, 3.0f);
 	cam.lookPosition = sol::Vec3f(0.0f);
 	cam.up = sol::Vec3f(0.0f, 1.0f, 0.0f);
 	cam.xOffset = 0.0f;
	cam.yOffset = 0.0f;

	projection = sol::Perspective(sol::Radians(cam.fov),this->GetWindow()->AspectRatio(), 0.1f, 1000.0f);
	view = sol::Transpose(sol::LookAt(cam.position, cam.lookPosition));
	model = sol::Mat4f(1.0f);
}

Renderer::~Renderer()
{
	// Delete VAO and VBO
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	
	// Delete all Materials
	// This will call Shader destructor and effectively cleanup all OpenGL shaders and programs
	this->GetObjectHandler().Materials().clear();
}

static const sol::Vec2f GetCursorPos(Renderer* renderer)
{
	Window* const window = renderer->GetWindow();
	GLFWwindow* context = window->Context();
	Camera* camera = &renderer->GetCamera();
	// just for extra safety
	if (window && context && camera)
	{
		double x, y;
		glfwGetCursorPos(context, &x, &y);
		// Screen coordinates -> Normalized Device Coordinates [-1; 1]
		float width = 2.0f * x / window->Width() - 1.0f;
		float height = 1.0f - 2.0f * y / window->Height();
		sol::Vec2f position = sol::Vec2f{ camera->xOffset + width * camera->xRenderBorder, camera->yOffset + height * camera->yRenderBorder };
		return position;
	}
	return {};
}

static sol::Vec2f cursorPos = {};

// This method will be called each frame in main loop
void Renderer::Update()
{
	Camera& camera = this->GetCamera();
	camera.Update(this->GetWindow()->AspectRatio());

	cursorPos = ::GetCursorPos(this);
	projection = sol::Perspective(sol::Radians(camera.fov), this->GetWindow()->AspectRatio(), 0.1f, 1000.0f);
	view = sol::LookAt(camera.position, camera.lookPosition);

	RenderDrawData([&](const Shader& shader) -> void 
	{
		shader.SetUniformMat4("u_Projection", projection);
		shader.SetUniformMat4("u_View", view);
	});
}

// This ImGui context method will be called each frame in main loop
void Renderer::ImGuiUpdate(ImGuiIO& io) 
{
	static bool objectCreation = false;
	static bool materialCreation = false;

	ObjectHandler& handler = GetObjectHandler();

	ImGui::Begin("Cartesian Plotter Debug");
	::ImGuiObjectControlMenu(handler, &objectCreation);
   	::ImGuiMaterialControlMenu(handler, &materialCreation);
   	::ImGuiCursorInfoMenu(handler, cursorPos);
    ImGui::TextColored({0.7f, 0.7f, 0.7f, 1.0f}, "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	if (objectCreation) ::ImGuiObjectCreationMenu(handler, &objectCreation);
	if (materialCreation) ::ImGuiMaterialCreationMenu(handler, &materialCreation);
}

/*
As of 31.05 this method no longer implements dynamic batching
Drawcall is being called per each object that is in DynamicBatching map
*/
void Renderer::RenderDrawData(std::function<void(const Shader&)> renderCallback)
{
	Camera& camera = this->GetCamera();
	ObjectHandler& handler = this->GetObjectHandler();
	std::vector<Object>& objects = handler.Objects();
	sol::Vec2f cursorPos = ::GetCursorPos(this);
	size_t offset = 0;
	for (Object& object : objects)
	{
		if (!camera.IsVisible(object))
		{
			continue;
		}
		const Material* material = object.GetMaterial();
		if (!material)
		{
			continue;
		}

		sol::Mat4f model = object.ConstructModel();
		
		const std::vector<Vertex>& objectVertices = object.Vertices();		
		
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), objectVertices.size() * sizeof(Vertex), objectVertices.data());

		const Shader& shader = material->GetShader();
		shader.Bind();
		shader.SetUniformMat4("u_Model", model);
		object.CallUniformCallback(shader, object);
		renderCallback(shader);

		glDrawArrays(material->GetRenderMode(), offset, objectVertices.size());
		offset = (offset + objectVertices.size()) % m_Vertices;

		// AABB Render Part
		if (object.RenderAABB())
		{
			Material* aabbMaterial = m_ObjectHandler->FindMaterial("AABB_Material");
			if (aabbMaterial)
			{
				const Shader& aabbShader = aabbMaterial->GetShader();

				AABB aabb = object.GetAABB();	
				aabb = aabb.Transform(model);

				bool collides = false;

				if (object.Collider())
				{
					collides = std::any_of(objects.begin(), objects.end(), [&](const Object& other) -> bool
					{
						if (&other != &object && other.Collider())
						{
							AABB otherAabb = other.GetAABB();
							otherAabb = otherAabb.Transform(other.ConstructModel());
							return aabb.CollideWith(otherAabb);
						}
						return false;
					});
				}

				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), 4 * sizeof(Vertex), reinterpret_cast<Vertex*>(&aabb));
				
				aabbShader.Bind();
				aabbShader.SetUniformBool("u_Collides", collides);
				renderCallback(aabbShader);

				glDrawArrays(aabbMaterial->GetRenderMode(), offset, 4);
				offset = (offset + 4) % m_Vertices;
			}
		}
	}
}

static void LoadScene(Renderer* renderer)
{
	ObjectHandler& handler = renderer->GetObjectHandler();
	Material temp = Material("Basic", GL_LINES);
	Material aabbMaterial = Material("AABBShader", GL_LINE_LOOP);
	/*
	Should use std::move for materials, as the Shader's copy-constructor
	is not about deep-copying. Also if we change the basicMaterial variable, we wont
	affect the material, that is copied into ObjectHandler object, thus its ambiguous to copy
	*/
	handler.AddMaterial("Basic_Material", std::move(temp));
	handler.AddMaterial("AABB_Material", std::move(aabbMaterial));
	Material* basicMaterial = handler.FindMaterial("Basic_Material");
	sol::Vec4f blue = sol::Vec4f(0.4f, 0.5f, 0.7f, 0.3f);
	sol::Vec4f white = sol::Vec4f(0.9f, 0.9f, 0.9f, 0.5f);
	Object scene = Object({}, basicMaterial, false);
	// we won't start from 20 and 10, so that
	// the scene would look more like a grid, than a chess board
	for (float f = -19.0f; f < 20; f += 1.0f)
	{
		scene.AddVertices
		({
			Vertex(f, -10.0f, blue),
			Vertex(f,  10.0f, blue),
		});
	}
	for (float f = -9.0f; f < 10; f += 1.0f)
	{
		scene.AddVertices
		({
			Vertex(-20.0f, f, blue),
			Vertex( 20.0f, f, blue),
		});
	}
	scene.AddVertices
	({
		Vertex(-21.0f, 0.0f, white),
		Vertex( 21.0f, 0.0f, white),
		// axis arrows
		Vertex(20.8f,  0.2f, white),
		Vertex(21.0f,  0.0f, white),
		Vertex(20.8f, -0.2f, white),
		Vertex(21.0f,  0.0f, white),
	});
	scene.AddVertices
	({
		Vertex(0.0f, -11.0f, white),
		Vertex(0.0f,  11.0f, white),
		// axis arrows
		Vertex(-0.2f, 10.8f, white),
		Vertex( 0.0f, 11.0f, white),
		Vertex( 0.2f, 10.8f, white),
		Vertex( 0.0f, 11.0f, white),
	});
	/* As of 02.06
	We should use std::move for object, as we wont be able to affect those objects,
	that are being rendered with this variables, thus it's ambiguous to make a copy,
	which leads to new UUID generation
	*/
	scene.SetSealed(true);
	scene.CreateAABB();
	handler.AddObject(std::move(scene));
}

static void ImGuiObjectControlMenu(ObjectHandler& handler, bool* objectCreation)
{
	if (ImGui::TreeNode("Object Control Menu"))
	{
		int currentIndex = handler.GetCurrentIndex();
		// Object list
		if (ImGui::BeginTable("Object list", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
		{
			ImGui::TableHeadersRow();
			ImGui::TableSetColumnIndex(0); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "UUID");
            ImGui::TableSetColumnIndex(1); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Bound Material");
            ImGui::TableSetColumnIndex(2); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Vertex Count");
			ImGui::TableNextRow();
			for (int i = 0; i < handler.Objects().size(); i++)
			{
				Object* object = handler.FindObject(i);
				if (!object->IsSealed())
				{
					Object* previousSelected = handler.FindObject(currentIndex);
					ImGui::TableSetColumnIndex(0);
					if (ImGui::Selectable(object->GetUUID().c_str(), object->Selected()))
					{
						std::cout << "Selected an object with UUID " << object->GetUUID() << std::endl;

						// Second condition just for ensurance and extra safety
						// Probably, may be removed at any time
						if (currentIndex != -1 && previousSelected)
						{
							previousSelected->Selected() = false;
						}
						handler.SetCurrentIndex(i);
						object->Selected() = true;
						ImGui::SetItemDefaultFocus();
					}
					ImGui::TableSetColumnIndex(1); ImGui::Text("%s", object->GetMaterial()->GetShader().Name().c_str());
					ImGui::TableSetColumnIndex(2); ImGui::Text("%lu", object->Vertices().size());
					ImGui::TableNextRow();
				}
			}
			ImGui::EndTable();
		}
		// Selected object control menu
		if (currentIndex != -1)
		{
			::ImGuiCurrentObjectMenu(handler, currentIndex);
		}
		// Create object
		if (ImGui::Button("Add Object"))
		{
			*objectCreation = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove Selection"))
		{
			if (currentIndex != -1)
			{
				handler.FindObject(currentIndex)->Selected() = false;
			}
			handler.SetCurrentIndex(-1);
		}
		ImGui::TreePop();
	}
}

static void ImGuiCurrentObjectMenu(ObjectHandler& handler, int currentIndex)
{
	if (ImGui::TreeNode("Current Object menu"))
	{
		static std::string materialChanger = "";
		static sol::Vec4f colorCache = {};				
		Object* object = handler.FindObject(currentIndex);
		if (object)
		{
			Material* mat = handler.FindMaterial(materialChanger);
			if (mat)
			{
				ImGui::TextColored(ImVec4(0.6f, 0.9f, 0.3f, 1.0f), "Currently bound Shader's name: %s", mat->GetShader().Name().c_str());					
				if (ImGui::Button("Apply Material"))
				{
					object->SetMaterial(mat);
				}
			}
			if (ImGui::Checkbox("Render AABB", &object->RenderAABB()))
			{
				// check if object should render AABB, but there is no special material
				// specified for it
				if (object->RenderAABB() && !handler.FindMaterial("AABB_Material"))
				{
					std::cout << "No material with name AABB_Material was found. Not able to render AABB\n";
				}
			}
			ImGui::SliderAngle("Object's Rotation Angle", &object->Angle());
			ImGui::SliderFloat2("Object's Scale", reinterpret_cast<float*>(&object->Scale()), 0.2f, 10.0f);
			ImGui::SliderFloat2("Object's Translation", reinterpret_cast<float*>(&object->Transform()), -100.0f, 100.0f);
			ImGui::ColorPicker4("Object's Color", &colorCache.r);
			ImGui::SameLine();
			if (ImGui::Button("Change color"))
			{
				object->FillColor(colorCache);
			}
			ImGui::InputText("Material Name", &materialChanger);
			if (ImGui::Button("Delete Object"))
			{
				handler.RemoveObject(currentIndex);
				handler.SetCurrentIndex(-1);
			}
		}
		ImGui::TreePop();
	}
}

static void ImGuiMaterialControlMenu(ObjectHandler& handler, bool* materialCreation)
{
	static const Material* cachedMaterial = nullptr;	
	static const std::string* cachedMaterialName = nullptr;
	if (ImGui::TreeNode("Material List"))
    {
    	const ObjectHandler::Material_Map& map = handler.Materials();
    	if (ImGui::BeginTable("split1", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    	{
    		ImGui::TableHeadersRow();
			ImGui::TableSetColumnIndex(0); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Material Name");
            ImGui::TableSetColumnIndex(1); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Shader Name");
            ImGui::TableSetColumnIndex(2); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Render Mode (GL Primitives)");
    		for (const auto& pair : map)
	    	{
             	ImGui::TableNextRow(); 
	            ImGui::TableSetColumnIndex(0);
	            if (ImGui::Selectable(pair.first.c_str(), cachedMaterial == &pair.second))
	            {
					std::cout << "Selected a material with shader " << pair.second.GetShader().Name() << std::endl;
	            	cachedMaterial = &pair.second;
	            	cachedMaterialName = &pair.first;
	            }
	            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", pair.second.GetShader().Name().c_str());
	            ImGui::TableSetColumnIndex(2); ImGui::Text("0x%x", pair.second.GetRenderMode());
	    	}
	        ImGui::EndTable();
    	}
    	if (ImGui::Button("Add Material"))
    	{
			*materialCreation = true;
    	}
    	if (cachedMaterial)
    	{
    		ImGui::SameLine();
	    	if (ImGui::Button("Delete Material"))
	    	{
	    		handler.RemoveMaterial(*cachedMaterialName);
        		cachedMaterial = nullptr;
        		cachedMaterialName = nullptr;
	    	}
    	}
    	ImGui::TreePop();
    }
}

static void ImGuiObjectCreationMenu(ObjectHandler& handler, bool* objectCreation)
{
	ImGui::Begin("Object creation");
	static std::vector<Vertex> vertexCache;
	static Vertex pointCache;
	static std::string objectMatNameCache = "";
	ImGui::InputFloat2("Vertex coordinates", &pointCache.position.x);
	ImGui::ColorPicker4("Vertex color", &pointCache.color.r);
	if (ImGui::Button("Push vertex"))
	{
		if (std::find(vertexCache.begin(), vertexCache.end(), pointCache) == vertexCache.end())
		{
			vertexCache.push_back(pointCache);
			pointCache.position = {};
		}
	}
	if (ImGui::TreeNode("Saved data"))
	{
		if (ImGui::BeginTable("Current object's vertex data", 2))
		{
			ImGui::TableHeadersRow();
			ImGui::TableSetColumnIndex(0); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Vertex position");
            ImGui::TableSetColumnIndex(1); ImGui::TextColored({0.6f, 0.9f, 0.3f, 1.0f}, "Vertex color");
			ImGui::TableNextRow();
			for (size_t i = 0; i < vertexCache.size(); i++)
			{
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Vertex %lu: xy = (%.3f, %.3f)", i
					, vertexCache[i].position.x
					, vertexCache[i].position.y);
				ImGui::TableSetColumnIndex(1);
				sol::Vec3f col = vertexCache[i].color;
				ImGui::TextColored({col.r, col.g, col.b, 1.0f}
				, "rgb = (%.2f, %.2f, %.2f)", col.r, col.g, col.b);	// Make it display in hex!
				ImGui::TableNextRow();
			}
			ImGui::EndTable();
		}
		ImGui::TreePop();
	}
	ImGui::InputText("Object's material", &objectMatNameCache);
	if (ImGui::ArrowButton("Cancel", ImGuiDir_Left))
	{
		*objectCreation = false;
	}
	ImGui::SameLine();
	Material* m = handler.FindMaterial(objectMatNameCache);
	if (ImGui::Button("Create"))
	{
		if (!m || vertexCache.empty())
		{
			std::cout << "Error! Object cannot be created. Unknown material or no vertices were specified\n";
		}
		else
		{
			*objectCreation = false;
			Object ob = Object(std::move(vertexCache), m);
			ob.CreateAABB();
			handler.AddObject(std::move(ob));
		}
	}

	ImGui::End();
}

static void ImGuiMaterialCreationMenu(ObjectHandler& handler, bool* materialCreation)
{
	ImGui::Begin("Material Creation");
	static std::string matNameBuff = ""; // material buffer in material creation
	static std::string shaNameBuff = ""; // shader buffer in material creation
	static unsigned int renderModeBuff = 0;
	ImGui::InputText("Material Name", &matNameBuff);
	ImGui::InputText("GLSL Shader to be loaded from Data/", &shaNameBuff);
	if (ImGui::TreeNode("Render Modes"))
	{
		if (ImGui::Selectable("GL_LINES", renderModeBuff == GL_LINES)) renderModeBuff = GL_LINES;
		if (ImGui::Selectable("GL_LINE_STRIP", renderModeBuff == GL_LINE_STRIP)) renderModeBuff = GL_LINE_STRIP;
		if (ImGui::Selectable("GL_LINE_LOOP", renderModeBuff == GL_LINE_LOOP)) renderModeBuff = GL_LINE_LOOP;
		if (ImGui::Selectable("GL_TRIANGLES", renderModeBuff == GL_TRIANGLES)) renderModeBuff = GL_TRIANGLES;
		if (ImGui::Selectable("GL_TRIANGLE_STRIP", renderModeBuff == GL_TRIANGLE_STRIP)) renderModeBuff = GL_TRIANGLE_STRIP;
		if (ImGui::Selectable("GL_TRIANGLE_FAN", renderModeBuff == GL_TRIANGLE_FAN)) renderModeBuff = GL_TRIANGLE_FAN;
		ImGui::SetItemDefaultFocus();
		ImGui::TreePop();
	}
	if (ImGui::ArrowButton("Cancel", ImGuiDir_Left))
	{
		*materialCreation = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Create"))
	{
		*materialCreation = false;
		handler.AddMaterial(matNameBuff, Material(shaNameBuff.c_str(), renderModeBuff));
	}
	ImGui::End();
}

static void ImGuiCursorInfoMenu(ObjectHandler& handler, const sol::Vec2f cursorPos)
{
	ImGui::TextColored({0.3f, 0.6f, 0.9f, 1.0f}, "Cursor position: %.2f, %.2f", cursorPos.x, cursorPos.y);
}