#include "Ground.h"
#include "Application.h"
#include <iostream>
namespace Renderable
{
    Ground::Ground(std::weak_ptr<Renderer::Shader> shader)
        : m_Prog(shader.lock())
    {
        const int gridSize = 100;  // Number of grid cells in each dimension
        const float cellSize = 100.0f;  // Size of each grid cell
        const int numVertices = (gridSize + 1) * (gridSize + 1);
        const int numTriangles = gridSize * gridSize * 2;
        const int numIndices = numTriangles * 3;

        std::vector<GLfloat> vertexData(numVertices * 5);
        std::vector<GLuint> indexData(numIndices);

        // Generate vertex positions and texture coordinates
        for (int row = 0; row <= gridSize; ++row)
        {
            for (int col = 0; col <= gridSize; ++col)
            {
                int index = (row * (gridSize + 1) + col) * 5;

                // Calculate vertex position
                float x = col * cellSize - (gridSize / 2.0f) * cellSize;
                float z = row * cellSize - (gridSize / 2.0f) * cellSize;
                vertexData[index + 0] = x;
                vertexData[index + 1] = 0.0f;
                vertexData[index + 2] = z;

                // Set texture coordinates (tile within each square)
                vertexData[index + 3] = static_cast<GLfloat>(col % 2);
                vertexData[index + 4] = static_cast<GLfloat>(row % 2);
            }
        }

        // Generate triangle indices
        int indexOffset = 0;
        for (int row = 0; row < gridSize; ++row)
        {
            for (int col = 0; col < gridSize; ++col)
            {
                int vertexIndex = row * (gridSize + 1) + col;

                // Triangle 1
                indexData[indexOffset++] = vertexIndex;
                indexData[indexOffset++] = vertexIndex + 1;
                indexData[indexOffset++] = vertexIndex + gridSize + 1;

                // Triangle 2
                indexData[indexOffset++] = vertexIndex + gridSize + 1;
                indexData[indexOffset++] = vertexIndex + 1;
                indexData[indexOffset++] = vertexIndex + gridSize + 2;
            }
        }

        m_Prog->Bind();
        m_Pos = std::make_unique<glm::vec3>(0, 0, 0);
        m_Vao = std::make_unique<Renderer::VertexArray>();
        m_Vbo = std::make_unique<Renderer::VertexBuffer>(vertexData.data(), numVertices * 5 * sizeof(GLfloat));
        m_Ibo = std::make_unique<Renderer::IndexBuffer>(indexData.data(), numIndices);
        m_Tex = std::make_unique<Renderer::Texture>("Resources/Textures/Bricks_White.png");

        Renderer::VertexBufferLayout layout;
        layout.PushElement<GLfloat>(3, GL_FALSE);
        layout.PushElement<GLfloat>(2, GL_FALSE);
        m_Vao->AttatchVertexBuffer(*m_Vbo, layout);

        m_Tex->Bind(0);
        m_Prog->SetUniform4f("u_Colour", 0.5f, 0.5f, 0.5f, 1.0f);
    }
	Ground::~Ground()
	{
	}

	void Ground::OnUpdate()
	{
	}

	void Ground::OnRender()
	{
        //TODO: Abstract into texture manager class
        // 
        // the bind location is used for layering, not switching (ie albedo, roughness etc)
        // so all main textures will be at 0
        //
		m_Prog->Bind();
		m_Tex->Bind(0);
		m_Prog->SetUniform1i("u_Texture", 0);
		m_Prog->SetUniformMat4f("u_MVP", Application::TranslateModel(*m_Pos));


		Application::renderer.Draw(*m_Vao, *m_Ibo, *m_Prog);
	}

	void Ground::OnImGuiRender()
	{
	}

}
