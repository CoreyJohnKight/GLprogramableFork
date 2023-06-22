#pragma once
#include <memory>
#include "Chunk.h"

namespace Terrain
{
	std::unique_ptr<Chunk> GenerateTerrain(int x, int y);
}