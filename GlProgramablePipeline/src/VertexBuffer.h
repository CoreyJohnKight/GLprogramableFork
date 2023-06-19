#pragma once
#include <GL/glew.h>

namespace Renderer
{
	class VertexBuffer
	{
	private:
		GLuint m_RendererID;
	
	public:
		VertexBuffer(const void* data, GLuint sizeBytes);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;
	};
}