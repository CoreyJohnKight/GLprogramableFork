#include "Chunk.h"
namespace Terrain
{
	Chunk::Chunk(int x, int y)
		: m_X(x), m_Y(y)
	{
		m_ChunkData = nullptr;
	}

	void Chunk::SetData(std::unique_ptr<std::vector<std::vector<int>>> chunkData)
	{
		m_ChunkData = std::move(chunkData);
	}

}
