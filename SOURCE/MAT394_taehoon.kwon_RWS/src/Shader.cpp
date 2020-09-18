#include "Shader.h"

using namespace SimulationSection;

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::SetUniform1i(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetUniform1ui(const std::string& name, unsigned value) const
{
	glUniform1ui(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetUniform1f(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Shader::SetUniform3fv(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniform3fv(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
}

void Shader::SetUniform4fv(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, false, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); // &source[0]
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // char message[length]
		glGetShaderInfoLog(id, length, &length, message);

		char vertexMsg[7] = "vertex";
		char fragmentMsg[9] = "fragment";

		char* msg = 0;
		switch (type)
		{
		case GL_VERTEX_SHADER:		msg = vertexMsg;	break;
		case GL_FRAGMENT_SHADER:	msg = fragmentMsg;	break;
		}

		std::cout << "Failed to compile " << msg << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram(); // GLUint
	unsigned int vs, fs;

	vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}