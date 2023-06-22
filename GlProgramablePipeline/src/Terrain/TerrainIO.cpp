#include "TerrainIO.h"
#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
namespace Terrain
{
    std::unique_ptr<Chunk> LoadTerrainFile(int x, int y)
    {
        return nullptr;
    }

    void WriteTerrainFile(int x, int y, const std::vector<std::vector<int>>& data)
    {
        FILE* pFile;
        std::string filePath = "Resources/Map/CHUNK_" + std::to_string(x) + "_" + std::to_string(y) + ".ljcnk";
        fopen_s(&pFile, filePath.c_str(), "w");

        if (pFile != nullptr)
        {
            for (const auto& row : data)
            {
                for (const auto& value : row)
                {
                    fprintf_s(pFile, "%d ", value);
                }
                fprintf_s(pFile, "\n");
            }

            fclose(pFile);
            return;
        }
        std::cout << "Error writing to file: " << filePath << std::endl;
        assert(false);
    }

}
