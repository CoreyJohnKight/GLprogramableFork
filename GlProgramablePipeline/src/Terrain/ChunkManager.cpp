#include "ChunkManager.h"

namespace Terrain
{
	ChunkManager::ChunkManager(int x, int y)
	{
		m_ChunkTree = std::make_unique<ChunkTree>(x,y);
	}

}
