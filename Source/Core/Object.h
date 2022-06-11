#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>

// Project Includes
#include <Utility/UUID.h>
#include <Utility/AABB.h>
#include <Utility/Vertex.h>
#include <Core/Material.h>
#include <Core/Events.h>

/**
 * 	Object class is a wrapper for an array of vertices. It provides convenient interface 
 *  for translating, rotating and scaling vertices, and wrapping them into a single object
 * 	
 * 	AddVertices() method allows to add new vertices to an object. 
 * 	It's important to remember that AABB is not updated after adding vertices, so it should be done manually
 * 	by calling CreateAABB() method
 * 
 * 	Every object contains its own UUID. If copy constructor or copy operator is called, the new UUID is created. 
 * 	
 * 	UniformCallback is a function, that is called each time an object is being rendered.
 * 	May be used to set an object color according to object's state. 
 * 	By default UniformCallback is Events::OnObjectRender() function
 * 	@see @ref <Core/Events.h>
 * 
 * 	- 	Private field m_RenderAABB tells the renderer whether the AABB of the object should be rendered
 * 	- 	Private field m_IsSealed tells the renderer whether the object is modifiable. 
 * 		If false, there will be no object reference in ImGui window. The only way to modify a sealed object - via code.
 * 	- 	Private field m_IsCollider tells the renderer whether object should take place in AABB collision tests
 * 
 * 	Every object holds a pointer to a certain material, which is stored in ObjectHandler object.
 * 	Thus material can be easily changed at runtime
 * 	For more information about materials @see @ref <Core/Material.h>
 */
class Object
{
public:
	using UniformCallback = std::function<bool(const Shader&, Object&)>;
public:
	// Constructor of object with std::initializer_list for convenient object creation
	// For a reference see ::LoadScene() function in Core/Renderer.cpp
	Object(std::initializer_list<Vertex> list, Material* material, bool isCollider = true, UniformCallback uniformCallback = Events::OnObjectRender);
	// Constructor of object with rvalue vector
	Object(std::vector<Vertex>&& vector, Material* material, bool isCollider = true, UniformCallback uniformCallback = Events::OnObjectRender);
	
	// Custom copy- and move- constructors & operators

	// Copy constructor creates new UUID, creates new AABB
	Object(const Object&);
	// Move constructor steals all data from object, avoiding new UUID generation and AABB allocation
	// Old moved object won't be sealed, won't render it's AABB and will be a collider by default.
	// Moved object's material will be nullptr and vertices will be cleared
	Object(Object&&);
	// Same as copy constructor
	Object& operator=(const Object&);
	// Same as move constructor
	Object& operator=(Object&&);
	
	~Object() = default;
		
	// This method returns a ready-to-go MVP matrix
	sol::Mat4f RotationMat() const;
	sol::Mat4f ScaleMat() const;
	sol::Mat4f TranslationMat() const;
	// will push_back vertices to object's vertex array 
	void AddVertices(std::initializer_list<Vertex> vertices);
	// changes the color of each vertex in the object's current vertex array
	void FillColor(const sol::Vec4f color);
	// creates AABB from the object's current vertex array
	void CreateAABB();

	// UniformCallback is a function, that is called each time an object is being rendered.
	// Called right before Renderer::FrameCallback() callback
	void CallUniformCallback(const Shader& shader, Object& object) const { m_UniformCallback(shader, object); }
	void SetUniformCallback(const UniformCallback& callback) { m_UniformCallback = callback; }

	// Many getters and setters
	inline const Material* GetMaterial() { return m_Material; }
	inline void SetMaterial(Material* material) { m_Material = material; }

	constexpr inline float& Angle() { return m_RotationAngle; }
	constexpr inline const float& Angle() const { return m_RotationAngle; }
	constexpr inline sol::Vec3f& Scale() { return m_Scale; }
	constexpr inline const sol::Vec3f& Scale() const { return m_Scale; }
	constexpr inline sol::Vec3f& Transform() { return m_Transform; }
	constexpr inline const sol::Vec3f& Transform() const { return m_Transform; }

	inline AABB& GetAABB() { return *m_AABB.get(); }
	inline const AABB& GetAABB() const { return *m_AABB.get(); }
	constexpr inline const UUID::uuid& GetUUID() const { return m_UUID; }
	constexpr inline const std::vector<Vertex>& Vertices() const { return m_Vertices; }

	constexpr bool& Selected() { return m_Selected; }
	constexpr const bool& Selected() const { return m_Selected; }
	constexpr bool& RenderAABB() { return m_RenderAABB; }
	constexpr const bool& RenderAABB() const { return m_RenderAABB; }
	constexpr bool IsSealed() const { return m_IsSealed; }
	constexpr void SetSealed(bool isSealed) { m_IsSealed = isSealed; }
	constexpr bool& Collider() { return m_IsCollider; }
	constexpr const bool& Collider() const { return m_IsCollider; }
private:
	std::vector<Vertex> m_Vertices;

	// Components of MVP matrix, that can be modified at runtime
	float m_RotationAngle = 0.0f;
	sol::Vec3f m_Scale = sol::Vec3f(1.0f);
	sol::Vec3f m_Transform = sol::Vec3f(0.0f);

	bool m_Selected = false;
	bool m_RenderAABB = false;
	bool m_IsSealed = false;
	bool m_IsCollider;

	Material* m_Material;
	UUID::uuid m_UUID;
	std::unique_ptr<AABB> m_AABB;

	UniformCallback m_UniformCallback;
};

/**
 * 	ObjectHandler is a big wrapper above string-to-material map and object's array,
 * 	that provides convenient interface to work with objects and materials
 * 
 * 	Handler also provides a "cursor", that indicates, which is the currently selected object,
 * 	that helps to implement some stuff in ImGui later
 */
class ObjectHandler
{
public:
	using Material_Map = std::unordered_map<std::string, Material>;
	using Object_Array = std::vector<Object>;
public:
	ObjectHandler();

	// Be aware! If the key with the specified name exists, than the material WON'T be overriden,
	// according to https://en.cppreference.com/w/cpp/container/unordered_map/emplace
	void AddMaterial(const std::string&, const Material&);
	void AddMaterial(std::string&&, const Material&);
	void AddMaterial(std::string&&, Material&&);
	void AddMaterial(const std::string&, Material&&);
	// AssignMaterial is a workaround for material overriding. Currently not implemented as not needed
	// See https://en.cppreference.com/w/cpp/container/unordered_map/insert_or_assign for more info
	// void AssignMaterial(const std::string&, const Material&);	Materials are added with std::unordered_map::insert_or_assign()
	Material* FindMaterial(const std::string&);
	const Material* FindMaterial(const std::string&) const;
	void RemoveMaterial(const std::string&);

	void AddObject(const Object&);
	void AddObject(Object&&);
	Object* FindObject(size_t i);
	const Object* FindObject(size_t i) const;
	void RemoveObject(size_t i);

	// Getters and setters
	inline Object_Array& Objects() { return *m_Objects.get(); }
	inline const Object_Array& Objects() const { return *m_Objects.get(); }
	inline Material_Map& Materials() { return *m_Materials.get(); }
	inline const Material_Map& Materials() const { return *m_Materials.get(); }

	// returns the current object's index
	inline int GetCurrentIndex() const { return m_CurrentObject; }
	inline void SetCurrentIndex(int index) { m_CurrentObject = index; }    // No bound checking!
private:
	std::unique_ptr<Object_Array> m_Objects;
	std::unique_ptr<Material_Map> m_Materials;
	int m_CurrentObject;
};