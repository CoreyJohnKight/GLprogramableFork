#include "Renderer.h"

namespace Renderer
{
	void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shaderProg) const
	{
		shaderProg.Bind();
		vao.Bind();
		ibo.Bind();

		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

	}

	void Renderer::Init() const
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

}
