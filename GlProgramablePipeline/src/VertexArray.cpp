#include "VertexArray.h"

namespace Renderer
{

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AttatchVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();

		const auto& elements = layout.GetElements();
		GLuint offset = 0;

		for(GLuint i = 0; i < elements.size(); i++)
		{
			const auto& e = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (const void*)offset);
			offset += e.count * VertexLayoutElement::GetTypeSize(e.type);
		}
	}
	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
}
