#include "ChunkTree.h"
#include "TerrainIO.h"
#include "Terrain.h"
#include <Application.h>
#include <iostream>

namespace Terrain
{
	int ChunkTree::maxNodeDist = 3;

	ChunkTree::ChunkTree(int x, int y)
		:m_HeadX(x), m_HeadY(y)
	{
	}

	void ChunkTree::Init()
	{
		// Create chunks
		m_Chunks.resize(maxNodeDist + 1, std::vector<std::shared_ptr<Chunk>>(maxNodeDist + 1));
		for (int y = 0; y <= maxNodeDist; y++)
		{
			for (int x = 0; x <= maxNodeDist; x++)
			{
				m_Chunks[y][x] = std::make_shared<Chunk>(Application::renderer.GetShader(Renderer::ShaderType::BASIC_NO_TEXTURE),
					x, y);
				
				// Assign head
				if (y == maxNodeDist / 2 && x == maxNodeDist / 2)
				{
					std::cout << "Assigning head at: " << x << ", " << y << std::endl;
					m_Head = m_Chunks[y][x];
				}
			}
		}

		// Link chunks
		for (int y = 0; y <= maxNodeDist; y++)
		{
			for (int x = 0; x <= maxNodeDist; x++)
			{
				// Link neighbor pointers for the current Chunk
				if (x > 0)
					m_Chunks[y][x]->nextNode_Left = m_Chunks[y][x - 1];
				if (x < maxNodeDist)
					m_Chunks[y][x]->nextNode_Right = m_Chunks[y][x + 1];
				if (y > 0)
					m_Chunks[y][x]->nextNode_Up = m_Chunks[y - 1][x];
				if (y < maxNodeDist)
					m_Chunks[y][x]->nextNode_Down = m_Chunks[y + 1][x];
			}
		}

		////TODO: TEMP
		//m_Head->SetData(LoadTerrainFile(m_HeadX, m_HeadY));
		m_Head->m_ChunkData = nullptr;
		
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
