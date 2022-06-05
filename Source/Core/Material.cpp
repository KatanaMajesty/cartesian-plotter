#include <Core/Material.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& name)
: m_Name(name), m_Program(glCreateProgram())
, m_Vertex(glCreateShader(GL_VERTEX_SHADER)), m_Fragment(glCreateShader(GL_FRAGMENT_SHADER))
{
	std::cout << "Creating shader " << m_Name << std::endl;
	std::string vertexName("../Data/" + name + ".vert");
	std::string fragmentName("../Data/" + name + ".frag");

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

Shader::Shader(Shader&& other)
: m_Name(other.m_Name), m_Program(other.m_Program), m_Vertex(other.m_Vertex), m_Fragment(other.m_Fragment)
, m_UniformCache(std::move(other.m_UniformCache))
{
	other.m_Program = {};
	other.m_Vertex = {};
	other.m_Fragment = {};
	other.m_Name = "";
}

Shader& Shader::operator=(const Shader& other)
{
	m_Program = other.m_Program;
	m_Vertex = other.m_Vertex;
	m_Fragment = other.m_Fragment;
	m_Name = other.m_Name;

	return *this;
}

Shader& Shader::operator=(Shader&& other)
{
	m_Program = other.m_Program;
	m_Vertex = other.m_Vertex;
	m_Fragment = other.m_Fragment;
	m_Name = other.m_Name;

	other.m_Program = {};
	other.m_Vertex = {};
	other.m_Fragment = {};
	other.m_Name = "";

	return *this;
}

Shader::~Shader()
{
	glDetachShader(m_Program, m_Vertex);
    glDetachShader(m_Program, m_Fragment);

	glDeleteShader(m_Vertex);
	glDeleteProgram(m_Fragment);

	glDeleteProgram(m_Program);
}

void Shader::SetUniformMat4(const char* uniform, const glm::mat4& mat) const 
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.emplace(uniform, location);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::SetUniformVec4(const char* uniform, const glm::vec4& vec) const 
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.emplace(uniform, location);
	glUniform4fv(location, 1, glm::value_ptr(vec));
}
void Shader::SetUniformVec3(const char* uniform, const glm::vec3& vec) const 
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.emplace(uniform, location);
	glUniform3fv(location, 1, glm::value_ptr(vec));

}
void Shader::SetUniformVec2(const char* uniform, const glm::vec2& vec) const
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.emplace(uniform, location);
	glUniform2fv(location, 1, glm::value_ptr(vec));
}

void Shader::SetUniformBool(const char* uniform, bool state) const
{
	auto iterator = m_UniformCache.find(uniform);
	unsigned int location = iterator == m_UniformCache.end() ? glGetUniformLocation(m_Program, uniform) : iterator->second;
	m_UniformCache.emplace(uniform, location);
	glUniform1i(location, state);
}

void Shader::Bind() const
{
	// std::cout << "Shader::Bind program id: " << m_Program << std::endl;
	glUseProgram(m_Program);
}

bool Shader::operator==(const Shader& other) const
{
	return this->m_Program == other.m_Program;
}

bool Shader::operator!=(const Shader& other) const
{
	return !(*this == other);
}

Material::Material(const std::string& shaderName, unsigned int renderMode)
: m_Shader(Shader(shaderName)), m_RenderMode(renderMode) {}

Material::Material(std::string&& shaderName, unsigned int renderMode)
: m_Shader(Shader(std::move(shaderName))), m_RenderMode(renderMode) {}


Material::Material(Material&& other)
: m_Shader(std::move(other.m_Shader)), m_RenderMode(other.m_RenderMode)
{
	other.m_RenderMode = {};
}

Material& Material::operator=(const Material& other)
{
	m_Shader = other.m_Shader;
	m_RenderMode = other.m_RenderMode;

	return *this;
}

Material& Material::operator=(Material&& other)
{
	m_Shader = std::move(other.m_Shader);
	m_RenderMode = other.m_RenderMode;

	other.m_RenderMode = {};

	return *this;
}

bool Material::operator==(const Material& other) const
{
	return this->m_Shader == other.m_Shader 
		&& this->m_RenderMode == other.m_RenderMode;
}

bool Material::operator!=(const Material& other) const
{
	return !(*this == other);
}
