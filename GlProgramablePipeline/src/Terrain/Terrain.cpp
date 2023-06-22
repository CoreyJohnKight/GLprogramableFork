#include "Terrain.h"
#include "TerrainDef.h"
#include "TerrainIO.h"
#include "Prng.h"
namespace Terrain
{
	std::unique_ptr<Chunk> GenerateTerrain(int x, int y)
	{
		std::unique_ptr<Chunk> chunk = std::make_unique<Chunk>(x, y);

		//TODO STUB
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				if(y >= 6)
					(*chunk->m_ChunkData)[y][x] = 0;
				else if(y >= 4)
					(*chunk->m_ChunkData)[y][x] = Prng::randomInt(0,2) == 1 ? 0 : 1;
				else
					(*chunk->m_ChunkData)[y][x] = 1;

			}
		}

		WriteTerrainFile(x, y, (*chunk->m_ChunkData));

		return chunk;
	}
}
