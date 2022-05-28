#include <Core/Shader.h>

#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* name)
: m_Program(glCreateProgram())
{
	std::string vertexName("../Data/" + std::string(name) + ".vert");
	std::string fragmentName("../Data/" + std::string(name) + ".frag");

	std::string v_Source;
	std::string f_Source;

	std::ifstream file;
	file.exceptions(std::ios_base::badbit);
	try {
		std::stringstream stream;
		
		file.open(vertexName);
		stream << file.rdbuf();
		v_Source = stream.str();
		file.close();

		stream.str(std::string());
		file.open(fragmentName);
		stream << file.rdbuf();
		f_Source = stream.str();
		file.close();

	} catch (const std::ifstream::failure& exception) {
		std::cout << "Couldn't open or read file: " << exception.what() << std::endl;
	}

	unsigned int m_Vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int m_Fragment = glCreateShader(GL_FRAGMENT_SHADER);

	const char* c_VertexSource = v_Source.c_str();
	const char* c_FragmentSource = f_Source.c_str();

	glShaderSource(m_Vertex, 1, &c_VertexSource, nullptr);
	glShaderSource(m_Fragment, 1, &c_FragmentSource, nullptr);

	glCompileShader(m_Vertex);
    glCompileShader(m_Fragment);

    int success;
    char log[256];

    glGetShaderiv(m_Vertex, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(m_Vertex, 256, nullptr, log);
        std::cout << log << std::endl;
    }

    glGetShaderiv(m_Fragment, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(m_Fragment, 256, nullptr, log);
        std::cout << log << std::endl;
    }

    glAttachShader(m_Program, m_Vertex);
    glAttachShader(m_Program, m_Fragment);
    glLinkProgram(m_Program);

    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetProgramInfoLog(m_Program, 256, nullptr, log);
        std::cout << log << std::endl;
    }
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
	glDeleteShader(m_Vertex);
	glDeleteProgram(m_Fragment);
}

void Shader::SetUniformMat4(const char* uniform, const glm::mat4& mat)
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.insert(std::make_pair(uniform, location));
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::SetUniformVec4(const char* uniform, const glm::vec4& vec)
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.insert(std::make_pair(uniform, location));
	glUniform4fv(location, 1, glm::value_ptr(vec));
}
void Shader::SetUniformVec3(const char* uniform, const glm::vec3& vec)
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.insert(std::make_pair(uniform, location));
	glUniform3fv(location, 1, glm::value_ptr(vec));

}
void Shader::SetUniformVec2(const char* uniform, const glm::vec2& vec)
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.insert(std::make_pair(uniform, location));
	glUniform2fv(location, 1, glm::value_ptr(vec));
}

void Shader::Bind(const Shader& shader)
{
	glUseProgram(shader.m_Program);
}