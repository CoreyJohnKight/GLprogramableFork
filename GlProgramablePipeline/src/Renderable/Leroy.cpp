#include <ImGui/imgui.h>
#include "Leroy.h"
#include "Application.h"

namespace Renderable
{
	Leroy::Leroy()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
		rIncrement = 0.05f;
		gIncrement = 0.05f;
		bIncrement = 0.05f;

		GLfloat triPos[] = {
			    0.0f,      0.0f,  0.0f, 0.0f,
			  200.0f,      0.0f,  1.0f, 0.0f,
			  200.0f,    200.0f,  1.0f, 1.0f,
			    0.0f,    200.0f,  0.0f, 1.0f,
		};

		GLuint indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Prog = std::make_unique<Renderer::Shader>("Resources/Shaders/BasicVert.glsl", "Resources/Shaders/BasicFrag.glsl");
		m_Prog->Bind();
		
		m_Pos = std::make_unique<glm::vec3>(0, 0, 0);
		m_Vao = std::make_unique<Renderer::VertexArray>();
		m_Vbo = std::make_unique<Renderer::VertexBuffer>(triPos, 4 * 4 * sizeof(GLfloat));
		m_Ibo = std::make_unique<Renderer::IndexBuffer>(indicies, 6);
		m_Tex = std::make_unique<Renderer::Texture>("Resources/Textures/Leroy.png");


		Renderer::VertexBufferLayout layout;
		layout.PushElement<GLfloat>(2, GL_FALSE);
		layout.PushElement<GLfloat>(2, GL_FALSE);
		m_Vao->AttatchVertexBuffer(*m_Vbo, layout);

		m_Prog->SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);


		m_Tex->Bind();
		m_Prog->SetUniform1i("u_Texture", 0);

	}
	Leroy::~Leroy()
	{
	}
	void Leroy::OnUpdate()
	{
		if (r > 1.0f)
			rIncrement = -0.004f;
		else if (r < 0.3f)
			rIncrement = 0.005f;
		r += rIncrement;

		if (g > 1.0f)
			gIncrement = -0.006f;
		else if (r < 0.3f)
			gIncrement = 0.006f;
		g += gIncrement;

		if (b > 1.0f)
			bIncrement = -0.004f;
		else if (b < 0.3f)
			bIncrement = 0.004f;
		b += bIncrement;
	}
	void Leroy::OnRender()
	{
		m_Prog->Bind();
		m_Prog->SetUniform4f("u_Colour", r, g, b, 1.0f);

		glm::mat4 mat = Application::TranslateModel(*m_Pos);

		m_Prog->SetUniformMat4f("u_MVP", mat);

		Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}
	void Leroy::OnImGuiRender()
	{
		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f fps)", 1000 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SliderFloat3("Transform", &m_Pos->x, 0.0f, 640.0f);
		ImGui::End();
	}
}
