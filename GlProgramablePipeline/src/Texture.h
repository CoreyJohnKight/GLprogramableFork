#pragma once

#include "Renderer.h"
namespace Renderer
{
	class Texture
	{
	private:
		GLuint m_TexID;
		std::string m_FilePath;
		GLubyte* m_localBuffer;
		GLint m_Width, m_Height, m_BitsPerPixel;

	public:
		Texture(const std::string& filePath);
		~Texture();

		void Bind(GLuint slot = 0) const;
		void UnBind() const;

		inline GLint GetWidth() const { return m_Width; } 
		inline GLint GetHeight() const { return m_Height; } 
	};
}