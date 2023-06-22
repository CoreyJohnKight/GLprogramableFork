#include "ChunkTree.h"
#include "Chunk.h"
#include "TerrainIO.h"
#include "Terrain.h"
#include <memory>

namespace Terrain
{
	ChunkTree::ChunkTree(int x, int y)
		:m_HeadX(x), m_HeadY(y)
	{

	}

	void ChunkTree::AddChunk(int x, int y)
	{
		//TODO:
		// search tree, then generate if nullptr next
		std::unique_ptr<Chunk> newChunk = LoadTerrainFile(x, y);
		if (newChunk == nullptr)
		{
			newChunk = GenerateTerrain(x, y);
		}
	}

}
