#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
	Shader(const char* name);
	~Shader();

	inline constexpr unsigned int Program() const { return m_Program; }

	void SetUniformMat4(const char* uniform, const glm::mat4& mat);
	void SetUniformVec4(const char* uniform, const glm::vec4& vec);
	void SetUniformVec3(const char* uniform, const glm::vec3& vec);
	void SetUniformVec2(const char* uniform, const glm::vec2& vec);

	static void Bind(const Shader& shader);
private:
	unsigned int m_Program;
	unsigned int m_Vertex;
	unsigned int m_Fragment;

	// Uniform cache here is used in order to avoid redundant glGetUniformLocation calls
	// unordered map will store uniform locations instead
	std::unordered_map<const char*, unsigned int> m_UniformCache;
};