#pragma once
#include <memory>

#include "Chunk.h"

namespace Terrain
{
	static std::unique_ptr<Chunk> GenerateTerrain(int x, int y);

	static constexpr short CHUNK_SIZE = 8;
}