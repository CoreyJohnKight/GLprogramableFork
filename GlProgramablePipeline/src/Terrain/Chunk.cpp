#include "Chunk.h"
#include "Application.h"
namespace Terrain
{
	Chunk::Chunk(std::weak_ptr<Renderer::Shader> shader, int x, int y)
		: m_Prog(shader.lock()), m_X(x), m_Y(y)
	{
		m_ChunkData = nullptr;
	}


	void Chunk::SetData(std::unique_ptr<std::vector<std::vector<int>>> chunkData)
	{
		m_ChunkData = std::move(chunkData);
		if (m_ChunkData == nullptr)
			return;

		float step = CHUNK_SIZE * 1;
		GLfloat verticies[CHUNK_SIZE * (CHUNK_SIZE * 3)];
		int numVertices = CHUNK_SIZE * (CHUNK_SIZE * 3);
		int numIndices = (CHUNK_SIZE - 1 * CHUNK_SIZE - 1) * 6;
		std::vector<GLuint> indices;
		int idx = 0;

		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			int xOffset = 0;
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				verticies[(y * (CHUNK_SIZE * 3)) + x + (xOffset++)] = x * step;
				verticies[(y * (CHUNK_SIZE * 3)) + x + (xOffset++)] = (*m_ChunkData)[y][x] * 15;
				verticies[(y * (CHUNK_SIZE * 3)) + x + (xOffset)] = y * step;
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

		m_Pos = std::make_unique<glm::vec3>(0, 0, 0);
		m_Vao = std::make_unique<Renderer::VertexArray>();
		m_Vbo = std::make_unique<Renderer::VertexBuffer>(verticies, numVertices * sizeof(GLfloat));
		m_Ibo = std::make_unique<Renderer::IndexBuffer>(indices.data(), indices.size());

		Renderer::VertexBufferLayout layout;
		layout.PushElement<GLfloat>(3, GL_FALSE);
		m_Vao->AttatchVertexBuffer(*m_Vbo, layout);

		m_Prog->SetUniform4f("u_Colour", 0.2f, 0.8f, 0.2f, 1.0f);

	}

	void Chunk::OnRender()
	{
		m_Prog->Bind();
		m_Prog->SetUniformMat4f("u_MVP", Application::TranslateModel(*m_Pos));

		Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}

}
