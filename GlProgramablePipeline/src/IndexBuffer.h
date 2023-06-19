#pragma once
#include <GL/glew.h>

namespace Renderer
{
	class IndexBuffer
	{
	private:
		GLuint m_RendererID;
		GLuint m_IndexCount;

	public:
		IndexBuffer(const GLuint* data, GLuint count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		inline GLuint GetCount() const { return m_IndexCount; }
	};
}