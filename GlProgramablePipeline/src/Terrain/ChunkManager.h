#pragma once

#include <memory>
#include "ChunkTree.h"

namespace Terrain
{
	class ChunkManager
	{
	public:
		ChunkManager(int x, int y);
		std::unique_ptr<ChunkTree> m_ChunkTree;
	private:
	};
}