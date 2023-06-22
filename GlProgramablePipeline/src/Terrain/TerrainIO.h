#pragma once
#include <memory>

#include "Chunk.h"

namespace Terrain
{
	std::unique_ptr<std::vector<std::vector<int>>> LoadTerrainFile(int x, int y);
	void WriteTerrainFile(int x, int y, const std::vector<std::vector<int>>& data);
}