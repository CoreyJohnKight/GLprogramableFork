#pragma once
#include <memory>

#include "Chunk.h"

namespace Terrain
{
	static std::unique_ptr<Chunk> LoadTerrainFile(int x, int y);

}