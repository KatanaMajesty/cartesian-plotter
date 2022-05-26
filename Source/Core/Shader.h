#pragma once

class Shader
{
public:
	Shader(const char* name);
	~Shader();

	static void Bind(const Shader& shader);
private:
	unsigned int m_Program;
	unsigned int m_Vertex;
	unsigned int m_Fragment;
};