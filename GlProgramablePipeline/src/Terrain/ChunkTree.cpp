#include "ChunkTree.h"
#include "TerrainIO.h"
#include "Terrain.h"

namespace Terrain
{
	ChunkTree::ChunkTree(int x, int y)
		:m_HeadX(x), m_HeadY(y)
	{
		m_Head = std::make_unique<Chunk>(x, y);
		m_Head->SetData(LoadTerrainFile(x, y));
		if(m_Head == nullptr)
			m_Head->SetData(GenerateTerrain(x, y));
	}

	void ChunkTree::AddChunk(int x, int y)
	{
		//TODO:
		// search tree, then generate if nullptr next
	}
}
