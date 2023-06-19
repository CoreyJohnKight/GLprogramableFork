#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Renderer
{
	class VertexArray
	{
	private:
		GLuint m_RendererID;

	public:
		VertexArray();
		~VertexArray();
		
		void AttatchVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void UnBind() const;
	};
}