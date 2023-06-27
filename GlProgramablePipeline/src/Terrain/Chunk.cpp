#include "Chunk.h"
#include "Application.h"
#include <ImGui/imgui.h>
#include <iostream>

namespace Terrain
{
	Chunk::Chunk(std::weak_ptr<Renderer::Shader> shader, int x, int y)
		: m_Prog(shader.lock()), m_X(x), m_Y(y)
	{
		m_ChunkData = nullptr;
		std::cout << "Chunk created at: " << x << ", " << y << std::endl;
	}


	void Chunk::SetData(std::unique_ptr<std::vector<std::vector<int>>> chunkData)
	{
		m_ChunkData = std::move(chunkData);
		if (m_ChunkData == nullptr)
			return;

		float step = 100;
		std::vector<GLfloat> verticies;
		std::vector<GLuint> indices;
		int idx = 0;

		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				// Calculate vertex pos
				glm::vec3 vertexPosition(x * step, (*m_ChunkData)[y][x] * 15, y * step);
				verticies.push_back(vertexPosition.x);
				verticies.push_back(vertexPosition.y);
				verticies.push_back(vertexPosition.z);

				float heightLeft = x > 0 ? (*m_ChunkData)[y][x - 1] : (*m_ChunkData)[y][x];
				float heightRight = x < CHUNK_SIZE - 1 ? (*m_ChunkData)[y][x + 1] : (*m_ChunkData)[y][x];
				float heightUp = y > 0 ? (*m_ChunkData)[y - 1][x] : (*m_ChunkData)[y][x];
				float heightDown = y < CHUNK_SIZE - 1 ? (*m_ChunkData)[y + 1][x] : (*m_ChunkData)[y][x];

				// Construct normal vector
				glm::vec3 normal(heightLeft - heightRight, 2.0f, heightDown - heightUp);

				// Calculate the average normal
				normal = glm::normalize(normal);

				// Store the normal in the vertices vector
				verticies.push_back(normal.x);
				verticies.push_back(normal.y);
				verticies.push_back(normal.z);
			}
		}

		// Calculate the indices for the grid
		for (int y = 0; y < CHUNK_SIZE - 1; y++)
		{
			for (int x = 0; x < CHUNK_SIZE - 1; x++)
			{
				int topLeft = y * CHUNK_SIZE + x;
				int topRight = topLeft + 1;
				int bottomLeft = (y + 1) * CHUNK_SIZE + x;
				int bottomRight = bottomLeft + 1;

				// Triangle 1
				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);

				// Triangle 2
				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}

		m_Prog->Bind();

		m_Pos = std::make_unique<glm::vec3>(0, -100, 0);
		m_Vao = std::make_unique<Renderer::VertexArray>();
		m_Vbo = std::make_unique<Renderer::VertexBuffer>(verticies.data(), verticies.size() * sizeof(GLfloat));
		m_Ibo = std::make_unique<Renderer::IndexBuffer>(indices.data(), indices.size());

		Renderer::VertexBufferLayout layout;
		layout.PushElement<GLfloat>(3, GL_FALSE);
		layout.PushElement<GLfloat>(3, GL_FALSE);
		m_Vao->AttatchVertexBuffer(*m_Vbo, layout);

		m_Prog->SetUniform4f("u_Colour", 0.2f, 0.8f, 0.2f, 1.0f);

	}

	void Chunk::OnRender()
	{
		m_Prog->Bind();
		m_Prog->SetUniformMat4f("u_MVP", Application::TranslateModel(*m_Pos));
		m_Prog->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), *m_Pos));
		m_Prog->SetUniform4fv("u_LightCol", Application::renderer.MainLightCol);
		m_Prog->SetUniform3fv("u_LightPos", Application::renderer.MainLightPos);
		m_Prog->SetUniform3fv("u_CamPos", Application::cameraPosition);


		Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}

}
