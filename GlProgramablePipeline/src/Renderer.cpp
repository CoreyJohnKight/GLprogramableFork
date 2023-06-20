#include "Renderer.h"
namespace Renderer
{
	void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
	{
		shader.Bind();
		vao.Bind();
		ibo.Bind();

		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

	}

	void Renderer::Init()
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		m_Shaders[BASIC] = std::make_shared<Shader>("Resources/Shaders/BasicVert.glsl", "Resources/Shaders/BasicFrag.glsl");
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	std::weak_ptr<Shader> Renderer::GetShader(ShaderType type)
	{
		return m_Shaders[type];
	}
}
