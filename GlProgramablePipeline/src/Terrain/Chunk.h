#pragma once
#include <memory>
#include <vector>
#include "TerrainDef.h"
#include "Renderable.h"
namespace Terrain
{
	class Chunk : public Renderer::Renderable
	{
	public:
		Chunk(std::weak_ptr<Renderer::Shader> shader, int x, int y);
		const int m_X;
		const int m_Y;
		void SetData(std::unique_ptr<std::vector<std::vector<int>>> chunkData);
		std::unique_ptr<std::vector<std::vector<int>>> m_ChunkData;
		void OnRender() override;
		std::shared_ptr<Chunk> nextNode_Up;
		std::shared_ptr<Chunk> nextNode_Down;
		std::shared_ptr<Chunk> nextNode_Left;
		std::shared_ptr<Chunk> nextNode_Right;
		bool isLoaded;

	private:
		std::unique_ptr<glm::vec3>				m_Pos;
		std::unique_ptr<Renderer::VertexArray>	m_Vao;
		std::unique_ptr<Renderer::VertexBuffer>	m_Vbo;
		std::unique_ptr<Renderer::IndexBuffer>	m_Ibo;
		std::shared_ptr<Renderer::Shader>		m_Prog;
	};
}