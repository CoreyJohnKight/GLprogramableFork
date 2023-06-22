#include "Terrain.h"
#include "TerrainDef.h"
#include "TerrainIO.h"
#include "Prng.h"
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
				if(y >= 6)
					(*chunkData)[y][x] = 0;
				else if(y >= 4)
					(*chunkData)[y][x] = Prng::randomInt(0,2) == 1 ? 0 : 1;
				else
					(*chunkData)[y][x] = 1;
			}
		}

		WriteTerrainFile(x, y, (*chunkData));

		return chunkData;
	}
}
