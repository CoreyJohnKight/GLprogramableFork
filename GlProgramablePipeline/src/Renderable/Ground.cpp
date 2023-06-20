#include "Ground.h"
#include "Application.h"
namespace Renderable
{
	Ground::Ground(std::weak_ptr<Renderer::Shader> shader)
		:m_Prog(shader.lock())
	{
		GLfloat triPos[] = {
			 -600.0f,   0.0f, -600.0f,  0.0f, 0.0f,
			  600.0f,   0.0f, -600.0f,  1.0f, 0.0f,
			  600.0f,   0.0f,  600.0f,  1.0f, 1.0f,
			 -600.0f,   0.0f,  600.0f,  0.0f, 1.0f,
		};

		GLuint indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Prog->Bind();

		m_Pos = std::make_unique<glm::vec3>(0, 0, 0);
		m_Vao = std::make_unique<Renderer::VertexArray>();
		m_Vbo = std::make_unique<Renderer::VertexBuffer>(triPos, 5 * 4 * sizeof(GLfloat));
		m_Ibo = std::make_unique<Renderer::IndexBuffer>(indicies, 6);
		m_Tex = std::make_unique<Renderer::Texture>("Resources/Textures/Bricks_White.png");

		Renderer::VertexBufferLayout layout;
		layout.PushElement<GLfloat>(3, GL_FALSE);
		layout.PushElement<GLfloat>(2, GL_FALSE);
		m_Vao->AttatchVertexBuffer(*m_Vbo, layout);

		m_Tex->Bind();
		m_Prog->SetUniform1i("u_Texture", 0);
		m_Prog->SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);
	}

	Ground::~Ground()
	{
	}

	void Ground::OnUpdate()
	{
	}

	void Ground::OnRender()
	{
		m_Tex->Bind();
		m_Prog->Bind();
		m_Prog->SetUniformMat4f("u_MVP", Application::TranslateModel(*m_Pos));

		Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}

	void Ground::OnImGuiRender()
	{
	}

}
