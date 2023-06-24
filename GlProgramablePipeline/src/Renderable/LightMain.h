# pragma once
#include "Renderable.h"

#include <memory>

namespace Renderable
{
	class LightMain : public Renderer::Renderable
	{
	public:
		LightMain(std::weak_ptr<Renderer::Shader> shader);
		~LightMain() override;

		void OnRender() override;
	private:
		std::unique_ptr<glm::vec3>				m_Pos;
		std::unique_ptr<Renderer::VertexArray>	m_Vao;
		std::unique_ptr<Renderer::VertexBuffer>	m_Vbo;
		std::unique_ptr<Renderer::IndexBuffer>	m_Ibo;
		std::shared_ptr<Renderer::Shader>		m_Prog;
	};
}