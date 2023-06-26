#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>

#include "glm/gtc/matrix_transform.hpp"

namespace Renderer
{
	class Shader
	{
	private:
		std::string m_VertPath;
		std::string m_FragPath;
		GLuint m_ProgramID;
		std::unordered_map<std::string, GLint> m_UniformLocationCahce;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, GLint value);
		void SetUniform3fv(const std::string& name, glm::vec3 vec);
		void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		void SetUniform4fv(const std::string& name, glm::vec4 vec);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	
	private:
		std::string ParseShader(const std::string filepath);
		GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		GLuint CompileShader(GLuint type, const std::string& source);

		GLint GetUniformLocation(const std::string& name);
	};
}