#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SimulationSection
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Set uniforms
		void SetUniform1i(const std::string& name, bool value) const;
		void SetUniform1i(const std::string& name, int value) const;
		void SetUniform1ui(const std::string& name, unsigned value) const;
		void SetUniform1f(const std::string& name, float value) const;
		void SetUniform3fv(const std::string& name, const glm::vec3& value) const;
		void SetUniform3fv(const std::string& name, float x, float y, float z) const;
		void SetUniform4fv(const std::string& name, const glm::vec4& value) const;
		void SetUniform4f(const std::string& name, float x, float y, float z, float w) const;
		void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const;

		unsigned int GetProgramID() { return m_RendererID; }

	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		int GetUniformLocation(const std::string& name);
	};
}