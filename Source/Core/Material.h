#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>
#include <unordered_map>
#include <Utility/Matrix.h>

class Material;

/**
 * 	@brief Shader class represents OpenGL program that holds GLSL shader source.
 * 	
 * 	This class provides convenient uniform setup, shader binding & efficient GLSL source parsing.
 */
class Shader
{
public:
	// UniformCache stores all uniform locations, that were used previously, 
	// which is much faster than many glGetUniformLocation() calls
	using UniformCache = std::unordered_map<const char*, unsigned int>;
public:
	Shader(const std::string&);
	Shader() = default;
	Shader(const Shader&) = default;
	Shader(Shader&&);
	Shader& operator=(const Shader&);
	Shader& operator=(Shader&&);
	~Shader();

	inline constexpr unsigned int Program() const { return m_Program; }
	inline constexpr const std::string& Name() const { return m_Name; }

	// Convenient uniform setters for all required types
	void SetUniformMat4(const char* uniform, const glm::mat4& mat) const;
	void SetUniformMat4(const char* uniform, const sol::Mat4f& mat) const;
	void SetUniformVec4(const char* uniform, const glm::vec4& vec) const;
	void SetUniformVec3(const char* uniform, const glm::vec3& vec) const;
	void SetUniformVec2(const char* uniform, const glm::vec2& vec) const;
	void SetUniformBool(const char* uniform, bool state) const;
	void Bind() const;
	
	// boolean comparison operators
	bool operator==(const Shader&) const;
	bool operator!=(const Shader&) const;

	// hash function is made friend to access private members without extra function calls
	friend std::hash<Material>;
private:
	// Shader stores it's name for convenience, despite the fact it is stored in Material
	std::string m_Name;
	// OpenGL Shader program id
	unsigned int m_Program;
	// vertex shader id
	unsigned int m_Vertex;
	// fragment shader id
	unsigned int m_Fragment;

	// UniformCache is mutable, as it's not entirely describes object's state, thus may be changed in const methods
	mutable UniformCache m_UniformCache;
};

/**
 * 	Material class represents a wrapper of Shader and renderMode
 * 
 * 	Class offers simple boolean operation, stream operators, getters and setters
 */
class Material
{
public:
	Material(const std::string& shaderName, unsigned int renderMode);
	Material(std::string&& shaderName, unsigned int renderMode);

	Material(const Material&) = default;
	Material(Material&&);
	Material& operator=(const Material&);
	Material& operator=(Material&&);

	~Material() = default;
	
	// boolean comparison operators
	bool operator==(const Material&) const;
	bool operator!=(const Material&) const;

	// ostream& operator override for Material
	friend std::ostream& operator<<(std::ostream& stream, const Material& material)
	{
		stream << material.GetRenderMode() << std::endl;
		stream << material.GetShader().Program();
		return stream;
	}

	// Getters and setters
	inline unsigned int GetRenderMode() const { return m_RenderMode; }
	inline Shader& GetShader() { return m_Shader; }
	inline const Shader& GetShader() const { return m_Shader; }
	
	// hash function is made friend to access private members without extra function calls
	friend std::hash<Material>;
private:
	Shader m_Shader;
	// Material's renderMode. E.g. GL_LINES, GL_TRIANGLES_FAN, etc.
	unsigned int m_RenderMode;
};

/**
 * 	This structure is used in order for std::unordered_map to
 *  be able to hash keys correctly
 */
template<> struct std::hash<Material>
{
	size_t operator() (const Material& material) const
	{
		// std::cout << "New hash!\n";
		// auto h1 = std::hash<std::string>{}(material.m_Name);
		auto h2 = std::hash<unsigned int>{}(material.m_Shader.m_Program);
		auto h3 = std::hash<unsigned int>{}(material.m_RenderMode);

		// Only for demonstration purposes, i.e. works but is overly simple
        // Rather use boost::hash_combine function
		return h2 ^ h3;
	}
};