#include "Shader.h"
#include <iostream>


namespace Renderer
{
    Shader::Shader(const std::string& vertPath, const std::string& fragPath)
        : m_VertPath(vertPath), m_FragPath(fragPath), m_ProgramID(0)
    {
        std::string vertexShader = ParseShader(vertPath);
        std::string fragmentShader = ParseShader(fragPath);

        m_ProgramID = CreateShader(vertexShader, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ProgramID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_ProgramID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform1i(const std::string& name, GLint value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    GLint Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCahce.find(name) != m_UniformLocationCahce.end())
            return m_UniformLocationCahce[name];

        GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    
        if (location == -1)
            std::cout << "Warning! Uniform " << name << " dosent exist!" << std::endl;

        m_UniformLocationCahce[name] = location;
        return location;
    }

    std::string Shader::ParseShader(const std::string filepath)
    {
        FILE* p_File;
        fopen_s(&p_File, filepath.c_str(), "r");

        if (p_File == NULL)
        {
            std::cout << "Failed to open file: " << filepath << std::endl;
            return "";
        }

        const int bufSize = 1024;
        char lineBuf[bufSize];
        std::string source;

        while (fgets(lineBuf, bufSize, p_File) != NULL)
        {
            source.append(lineBuf);
        }

        fclose(p_File);

        std::cout << "Succesfully loaded file: " << filepath << std::endl;
        
        return source;
    }

    GLuint Shader::CompileShader(GLuint type, const std::string& source)
    {
        GLuint shaderID = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(shaderID, 1, &src, nullptr);
        glCompileShader(shaderID);

        GLint result;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(shaderID, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(shaderID);

            return 0;
        }
        std::cout << "Compiled " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;

        return shaderID;
    }

    GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint program = glCreateProgram();
        GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

}