#pragma once
#include <memory>
#include <vector>
#include "TerrainDef.h"

namespace Terrain
{
	class Chunk
	{
	public:
		Chunk(int x, int y);
		const int m_X;
		const int m_Y;
		void SetData(std::unique_ptr<std::vector<std::vector<int>>> chunkData);
		std::unique_ptr<std::vector<std::vector<int>>> m_ChunkData;
	private:
	};
}