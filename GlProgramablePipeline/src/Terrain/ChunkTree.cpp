#include "ChunkTree.h"
#include "TerrainIO.h"
#include "Terrain.h"
#include <Application.h>
#include <iostream>

namespace Terrain
{
	int ChunkTree::maxNodeDist = 3;
	int ChunkTree::maxViewDist = 3;

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
					m_RealHead = m_Chunks[y][x];
					m_CurrentHead = m_Chunks[y][x];
					m_HeadX = x;
					m_HeadY = y;
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
		//m_RealHead->m_ChunkData = nullptr;
		//
		//if (m_RealHead->m_ChunkData == nullptr)
		//	m_RealHead->SetData(GenerateTerrain(m_HeadX, m_HeadY));

		WalkLoad(m_HeadX, m_HeadY, maxViewDist);
		
	}

	void ChunkTree::AddChunk(int x, int y)
	{
		//TODO:
		// search tree, then generate if nullptr next
	}
	void ChunkTree::Render()
	{
		WalkRender(m_HeadX, m_HeadY, maxViewDist);
		//m_RealHead->OnRender();
	}
	void ChunkTree::WalkLoad(int x, int y, int stepsRemaining)
	{
		// Steps check
		if (stepsRemaining == 0)
			return;
		// Bounds check
		if (x < 0 || x > maxNodeDist)
			return;
		if (y < 0 || y > maxNodeDist)
			return;

		std::shared_ptr<Chunk> current = m_Chunks[y][x];
		if (current == nullptr)
		{
			std::cout << "Null chunk found at: " << x << ", " << y << "!" << std::endl;
			assert(false);
		}

		//TODO: temp
		//current->SetData(LoadTerrainFile(x, y));

		if (current->isLoaded == false)
		{
			current->SetData(GenerateTerrain(x, y));
			std::cout << "Loaded chunk: " << x << ", " << y << "!" << std::endl;
		}
	
		WalkLoad(x + 1, y + 1, stepsRemaining - 1);
		WalkLoad(x + 1, y, stepsRemaining - 1);
		WalkLoad(x - 1, y, stepsRemaining - 1);
		WalkLoad(x - 1, y - 1, stepsRemaining - 1);
	}
	void ChunkTree::WalkRender(int x, int y, int stepsRemaining)
	{
		// Steps check
		if (stepsRemaining == 0)
			return;
		// Bounds check
		if (x < 0 || x > maxNodeDist)
			return;
		if (y < 0 || y > maxNodeDist)
			return;

		std::shared_ptr<Chunk> current = m_Chunks[y][x];
		if (current == nullptr)
		{
			std::cout << "Null chunk found at: " << x << ", " << y << "!" << std::endl;
			assert(false);
		}

		//TODO: temp
		//current->SetData(LoadTerrainFile(x, y));

		if (current->isLoaded == false)
		{
			std::cout << "Null chunk data found at: " << x << ", " << y << "!" << std::endl;
			assert(false);
		}
		else
		{
			current->OnRender();
		}

		WalkRender(x + 1, y + 1, stepsRemaining - 1);
		WalkRender(x + 1, y, stepsRemaining - 1);
		WalkRender(x - 1, y, stepsRemaining - 1);
		WalkRender(x - 1, y - 1, stepsRemaining - 1);
	}
}
