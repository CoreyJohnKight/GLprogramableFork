#pragma once
#include <memory>
#include "Chunk.h"

namespace Terrain
{
	std::unique_ptr<std::vector<std::vector<int>>> GenerateTerrain(int x, int y);
}