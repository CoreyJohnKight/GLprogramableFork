#include "LightMain.h"
#include "Application.h"

namespace Renderable
{
	LightMain::LightMain(std::weak_ptr<Renderer::Shader> shader)
    : m_Prog(shader.lock())
    {
        GLfloat triPos[] = {
            // Front face
            -50.0f, -50.0f, 50.0f,  // Bottom-left
            50.0f, -50.0f, 50.0f,   // Bottom-right
            50.0f, 50.0f, 50.0f,    // Top-right
            -50.0f, 50.0f, 50.0f,   // Top-left

            // Back face
            -50.0f, -50.0f, -50.0f, // Bottom-left
            50.0f, -50.0f, -50.0f,  // Bottom-right
            50.0f, 50.0f, -50.0f,   // Top-right
            -50.0f, 50.0f, -50.0f,  // Top-left

            // Left face
            -50.0f, -50.0f, -50.0f, // Bottom-back
            -50.0f, -50.0f, 50.0f,  // Bottom-front
            -50.0f, 50.0f, 50.0f,   // Top-front
            -50.0f, 50.0f, -50.0f,  // Top-back

            // Right face
            50.0f, -50.0f, -50.0f,  // Bottom-back
            50.0f, -50.0f, 50.0f,   // Bottom-front
            50.0f, 50.0f, 50.0f,    // Top-front
            50.0f, 50.0f, -50.0f,   // Top-back

            // Top face
            -50.0f, 50.0f, 50.0f,   // Front-left
            50.0f, 50.0f, 50.0f,    // Front-right
            50.0f, 50.0f, -50.0f,   // Back-right
            -50.0f, 50.0f, -50.0f,  // Back-left

            // Bottom face
            -50.0f, -50.0f, 50.0f,  // Front-left
            50.0f, -50.0f, 50.0f,   // Front-right
            50.0f, -50.0f, -50.0f,  // Back-right
            -50.0f, -50.0f, -50.0f, // Back-left
        };

        // Specify the indices for the cube faces
        GLuint indicies[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            8, 9, 10,
            10, 11, 8,

            // Right face
            12, 13, 14,
            14, 15, 12,

            // Top face
            16, 17, 18,
            18, 19, 16,

            // Bottom face
            20, 21, 22,
            22, 23, 20
        };

		m_Prog->Bind();

		m_Pos = std::make_unique<glm::vec3>(0, 0, 0);
		m_Vao = std::make_unique<Renderer::VertexArray>();
		m_Vbo = std::make_unique<Renderer::VertexBuffer>(triPos, 12 * 6 * sizeof(GLfloat));
		m_Ibo = std::make_unique<Renderer::IndexBuffer>(indicies, 36);

		Renderer::VertexBufferLayout layout;
		layout.PushElement<GLfloat>(3, GL_FALSE);
		m_Vao->AttatchVertexBuffer(*m_Vbo, layout);
	}

	LightMain::~LightMain()
	{
	}

	void LightMain::OnRender()
	{
        m_Prog->Bind();
        m_Prog->SetUniformMat4f("u_MVP", Application::TranslateModel(*m_Pos));
        m_Prog->SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);


        Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}

}
