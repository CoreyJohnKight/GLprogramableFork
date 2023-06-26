#include "ChunkTree.h"
#include "TerrainIO.h"
#include "Terrain.h"
#include <Application.h>

namespace Terrain
{
	ChunkTree::ChunkTree(int x, int y)
		:m_HeadX(x), m_HeadY(y)
	{

	}

	void ChunkTree::Init()
	{
		m_Head = std::make_unique<Chunk>(Application::renderer.GetShader(Renderer::ShaderType::BASIC_NO_TEXTURE), m_HeadX, m_HeadY);
		
		//TODO: TEMP
		m_Head->SetData(LoadTerrainFile(m_HeadX, m_HeadY));
		//m_Head->m_ChunkData = nullptr;

		if (m_Head->m_ChunkData == nullptr)
			m_Head->SetData(GenerateTerrain(m_HeadX, m_HeadY));
	}

	void ChunkTree::AddChunk(int x, int y)
	{
		//TODO:
		// search tree, then generate if nullptr next
	}
	void ChunkTree::Render()
	{
		m_Head->OnRender();
	}
}
