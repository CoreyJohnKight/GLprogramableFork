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
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		// Set the depth function
		//glDepthFunc(GL_LESS);

		//TODO: just store program id?
		// Shaders
		m_Shaders[BASIC] = std::make_shared<Shader>("Resources/Shaders/BasicVert.glsl", "Resources/Shaders/BasicFrag.glsl");
		
		m_Shaders[GROUND] = std::make_shared<Shader>("Resources/Shaders/GroundVert.glsl", "Resources/Shaders/GroundFrag.glsl");
	
		// Vao's

	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	std::weak_ptr<Shader> Renderer::GetShader(ShaderType type)
	{
		return m_Shaders[type];
	}
	std::weak_ptr<VertexArray> Renderer::GetVao(VaoType type)
	{
		return m_VAOs[type];
	}
}
