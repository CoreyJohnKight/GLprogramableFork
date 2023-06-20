#pragma once

#include <memory>
#include "../Renderable.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Texture.h"

namespace Renderable
{
	class Ground : public Renderer::Renderable
	{
	public:
		Ground(std::weak_ptr<Renderer::Shader> shader);
		~Ground() override;

		void OnUpdate() override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<glm::vec3>				m_Pos;
		std::unique_ptr<Renderer::VertexArray>	m_Vao;
		std::unique_ptr<Renderer::VertexBuffer>	m_Vbo;
		std::unique_ptr<Renderer::IndexBuffer>	m_Ibo;
		std::shared_ptr<Renderer::Shader>		m_Prog;
		std::unique_ptr<Renderer::Texture>		m_Tex;
	};
}