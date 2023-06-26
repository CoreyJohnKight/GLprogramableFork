#include "Terrain.h"
#include "TerrainDef.h"
#include "TerrainIO.h"
#include "Prng.h"
#include <glm/gtc/noise.hpp>
namespace Terrain
{
	std::unique_ptr<std::vector<std::vector<int>>> GenerateTerrain(int x, int y)
	{
		std::unique_ptr<std::vector<std::vector<int>>> chunkData = std::make_unique<std::vector<std::vector<int>>>(CHUNK_SIZE, std::vector<int>(CHUNK_SIZE));
		//TODO STUB
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				(*chunkData)[y][x] = glm::perlin(glm::vec3(x / 10.f, y / 10.f, 100.f)) * 10;

				//if(y >= 20)
				//	(*chunkData)[y][x] = Prng::randomInt(0, 0);
				//else if(y >= 10)
				//	(*chunkData)[y][x] = Prng::randomInt(4,5);
				//else
				//	(*chunkData)[y][x] = Prng::randomInt(7, 8);
			}
		}

		WriteTerrainFile(x, y, (*chunkData));

		return chunkData;
	}
}
