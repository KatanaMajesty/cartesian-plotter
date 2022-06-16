#include <Renderer.h>
#include <Core/Events.h>
#include <Core/Window.h>

static float zDelta = 0.5f;
static float moveDelta = 0.15f;

namespace Events
{
	bool OnWindowClose(Window* window)
	{		
		window->Close();
		return true;
	}

	bool OnKeyLeft(Window* window)
	{
		Camera& camera = window->RenderContext()->GetCamera();
		camera.offset.x -= moveDelta;
		return true;
	}
	bool OnKeyRight(Window* window)
	{
		Camera& camera = window->RenderContext()->GetCamera();
		camera.offset.x += moveDelta;
		return true;
	}
	bool OnKeyUp(Window* window)
	{
		Camera& camera = window->RenderContext()->GetCamera();
		camera.offset.y += moveDelta;
		return true;
	}
	bool OnKeyDown(Window* window)
	{
		Camera& camera = window->RenderContext()->GetCamera();
		camera.offset.y -= moveDelta;
		return true;
	}

	bool OnWindowResize(int width, int height, Window* window)
	{
		window->SetWidth(width);
		window->SetHeight(height);
		return false;
	}

	bool OnMouseScroll(double xoffset, double yoffset, ::Window* window)
	{
		Renderer* renderer = window->RenderContext();
		Camera& camera = renderer->GetCamera();
		if (yoffset > 0)
		{
			if (camera.offset.z > zDelta)
			{
				camera.offset.z -= zDelta;
			}
		}
		else
		{
			camera.offset.z += zDelta;
		}
		return true;
	}

	bool OnGLFWError(int error, const char* description)
	{
    	std::cout << "Glfw Error " << error << ": " << description << std::endl;
    	return true;
	}

	bool OnObjectRender(const Shader& shader, Object& object)
	{
		// Check if the object is selcted
		if (object.Selected())
		{
			// if it is selected, pass the state of object to shader and assign a new selected color
			shader.SetUniformBool("u_Selected", true);
			shader.SetUniformVec4("u_SelectedColor", sol::Vec4f(0.9f, 0.6f, 0.3f, 0.5f));
		}
		else
		{
			// if not - update a selected state in shader
			shader.SetUniformBool("u_Selected", false);
		}
		// if not selected - do nothing
		return true;
	}

	bool OnFrameUpdate(Window* window)
	{
		int state = glfwGetKey(window->Context(), GLFW_KEY_W);
		if (state == GLFW_PRESS) Events::OnKeyUp(window);

		state = glfwGetKey(window->Context(), GLFW_KEY_A);
		if (state == GLFW_PRESS) Events::OnKeyLeft(window);
		
		state = glfwGetKey(window->Context(), GLFW_KEY_S);
		if (state == GLFW_PRESS) Events::OnKeyDown(window);
		
		state = glfwGetKey(window->Context(), GLFW_KEY_D);
		if (state == GLFW_PRESS) Events::OnKeyRight(window);
		
		return true;
	}
};

