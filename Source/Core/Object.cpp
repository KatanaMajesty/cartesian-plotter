#include <Core/Object.h>

Object::Object(std::initializer_list<Vertex> list, Material* material, bool isCollider, std::function<bool(const Shader&, Object&)> uniformCallback)
: m_UniformCallback(uniformCallback), m_Vertices(list)
, m_Material(material), m_IsCollider(isCollider), m_UUID(UUID::Generate_UUID_V4())
{
}

Object::Object(std::vector<Vertex>&& vector, Material* material, bool isCollider, std::function<bool(const Shader&, Object&)> uniformCallback)
: m_UniformCallback(uniformCallback), m_Vertices(std::move(vector))
, m_Material(material), m_IsCollider(isCollider), m_UUID(UUID::Generate_UUID_V4())
{
}

sol::Mat4f Object::RotationMat() const
{
	return sol::RotateZ(this->Angle());
}

sol::Mat4f Object::ScaleMat() const
{
	return sol::Scale(this->Scale());
}

sol::Mat4f Object::TranslationMat() const
{
	return sol::Translate(sol::Mat4f(1.0f), this->Transform());
}

void Object::AddVertices(std::initializer_list<Vertex> vertices)
{
	std::for_each(vertices.begin(), vertices.end(), [&](const Vertex& vertex) { m_Vertices.push_back(vertex); });
}

void Object::FillColor(const sol::Vec4f color)
{
	for (Vertex& v : m_Vertices)
	{
		v.color = color;
	}
}

void Object::CreateAABB()
{
	this->m_AABB = std::make_unique<AABB>(AABB::Create(this->Vertices()));
}

Object::Object(const Object& other)
: m_Vertices(other.m_Vertices)
, m_UniformCallback(other.m_UniformCallback)
, m_RotationAngle(other.m_RotationAngle), m_Scale(other.m_Scale), m_Transform(other.m_Transform)
, m_Material(other.m_Material), m_IsCollider(other.m_IsCollider), m_UUID(UUID::Generate_UUID_V4())
, m_AABB(std::make_unique<AABB>(*other.m_AABB))
{
	m_Selected = other.m_Selected;
	m_RenderAABB = other.m_RenderAABB;
	m_IsSealed = other.m_IsSealed;
}

Object::Object(Object&& other)
: m_Vertices(std::move(other.m_Vertices))
, m_UniformCallback(std::move(other.m_UniformCallback))
, m_RotationAngle(other.m_RotationAngle), m_Scale(other.m_Scale), m_Transform(other.m_Transform)
, m_Material(other.m_Material), m_IsCollider(other.m_IsCollider), m_UUID(std::move(other.m_UUID))
, m_AABB(std::move(other.m_AABB))
{
	m_Selected = other.m_Selected;
	m_RenderAABB = other.m_RenderAABB;
	m_IsSealed = other.m_IsSealed;

	// We should also steal the state of previous object
	other.m_Selected = false;
	other.m_RotationAngle = 0.0f;
	other.m_Scale = sol::Vec3f(1.0f);
	other.m_Transform = sol::Vec3f(0.0f);
	other.m_Material = nullptr;
	other.m_IsCollider = true;
	other.m_RenderAABB = false;
	other.m_IsSealed = false;
}

Object& Object::operator=(const Object& other)
{
	if (this == &other)
        return *this;

	this->m_Vertices = other.m_Vertices;
	this->m_UniformCallback = other.m_UniformCallback;
	this->m_Selected = false;
	this->m_RotationAngle = other.m_RotationAngle;
	this->m_Scale = other.m_Scale;
	this->m_Transform = other.m_Transform;
	this->m_Material = other.m_Material;
	this->m_IsCollider = other.m_IsCollider;
	this->m_UUID = UUID::Generate_UUID_V4();
	this->m_AABB = std::make_unique<AABB>(*other.m_AABB);
	this->m_IsSealed = other.m_IsSealed;
	this->m_RenderAABB = false;

	return *this;
}

Object& Object::operator=(Object&& other)
{
	if (this == &other)
        return *this;

	this->m_Vertices = std::move(other.m_Vertices);
	this->m_UniformCallback = std::move(other.m_UniformCallback);
	this->m_Selected = other.m_Selected;
	this->m_RotationAngle = other.m_RotationAngle;
	this->m_Scale = other.m_Scale;
	this->m_Transform = other.m_Transform;
	this->m_Material = other.m_Material;
	this->m_IsCollider = other.m_IsCollider;
	this->m_UUID = std::move(other.m_UUID);
	this->m_AABB = std::make_unique<AABB>(*other.m_AABB);
	this->m_IsSealed = other.m_IsSealed;
	this->m_RenderAABB = other.m_RenderAABB;

	// We should also steal the state of previous object
	other.m_Selected = false;
	other.m_RotationAngle = 0.0f;
	other.m_Scale = sol::Vec3f(1.0f);
	other.m_Transform = sol::Vec3f(0.0f);
	other.m_Material = nullptr;
	other.m_IsCollider = true;
	other.m_AABB.reset();
	other.m_RenderAABB = false;
	other.m_IsSealed = false;
	other.m_IsSealed = false;
	other.m_RenderAABB = false;

	return *this;
}

ObjectHandler::ObjectHandler()
: m_Objects(std::make_unique<Object_Array>()), m_Materials(std::make_unique<Material_Map>())
, m_CurrentObject(-1)
{
}

Material* ObjectHandler::AddMaterial(const std::string& name, const Material& material)
{
	return &m_Materials->emplace(name, material).first->second;
}

Material* ObjectHandler::AddMaterial(std::string&& name, const Material& material)
{
	return &m_Materials->emplace(std::move(name), material).first->second;
}

Material* ObjectHandler::AddMaterial(std::string&& name, Material&& material)
{
	return &m_Materials->emplace(std::move(name), std::move(material)).first->second;
}

Material* ObjectHandler::AddMaterial(const std::string& name, Material&& material)
{
	return &m_Materials->emplace(name, std::move(material)).first->second;
}

Material* ObjectHandler::FindMaterial(const std::string& name)
{
	Material_Map::iterator it = m_Materials->find(name);
	if (it == m_Materials->end())
	{
		return nullptr;
	}
	return &it->second;
}

const Material* ObjectHandler::FindMaterial(const std::string& name) const
{
	Material_Map::const_iterator it = m_Materials->find(name);
	if (it == m_Materials->end())
	{
		return nullptr;
	}
	return &it->second;
}

void ObjectHandler::RemoveMaterial(const std::string& name)
{
	m_Materials->erase(name);
}

void ObjectHandler::AddObject(const Object& object)
{
	m_Objects->push_back(object);
}

void ObjectHandler::AddObject(Object&& object)
{
	m_Objects->push_back(std::move(object));
}

Object* ObjectHandler::FindObject(size_t i)
{
	if (i >= m_Objects->size())
	{
		return nullptr;
	}
	return (m_Objects->begin() + i).base(); 
}

const Object* ObjectHandler::FindObject(size_t i) const
{
	if (i >= m_Objects->size())
	{
		return nullptr;
	}
	return (m_Objects->begin() + i).base(); 
}

void ObjectHandler::RemoveObject(size_t i)
{
	if (i >= m_Objects->size())
	{
		std::cout << "ObjectHandler::RemoveObject() tried to remove out of bounds! Variable i = " << i << std::endl;
		return;
	}
	m_Objects->erase(m_Objects->begin() + i);
}