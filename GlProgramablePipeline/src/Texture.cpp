
#include "Texture.h"
#include "Stb_Image/stbImage.h"

#define RGBA 4

namespace Renderer
{

	Texture::Texture(const std::string& filePath)
		: m_TexID(0), m_FilePath(filePath), m_localBuffer(nullptr), 
		m_Width(0), m_Height(0), m_BitsPerPixel(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_localBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BitsPerPixel, RGBA);

		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE_2D, m_TexID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	
		if (m_localBuffer)
			stbi_image_free(m_localBuffer);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TexID);
	}

	void Texture::Bind(GLuint slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
