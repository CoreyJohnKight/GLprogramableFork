#include "Chunk.h"
#include "TerrainDef.h"
namespace Terrain
{
	Chunk::Chunk(int x, int y)
		: m_X(x), m_Y(y)
	{
		m_ChunkData = std::make_unique<std::vector<std::vector<int>>>(CHUNK_SIZE, std::vector<int>(CHUNK_SIZE));
	}

}
