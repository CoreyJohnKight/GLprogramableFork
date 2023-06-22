#include "TerrainIO.h"
#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
namespace Terrain
{
    std::unique_ptr<std::vector<std::vector<int>>> LoadTerrainFile(int x, int y)
    {
        FILE* pFile;
        std::string filePath = "Resources/Map/CHUNK_" + std::to_string(x) + "_" + std::to_string(y) + ".ljcnk";
        std::unique_ptr<std::vector<std::vector<int>>> data = nullptr;
        fopen_s(&pFile, filePath.c_str(), "r");

        if (pFile != nullptr)
        {
            std::unique_ptr<std::vector<std::vector<int>>> data = std::make_unique<std::vector<std::vector<int>>>(CHUNK_SIZE, std::vector<int>(CHUNK_SIZE));

            int value = 0;
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int x = 0; x < CHUNK_SIZE; x++)
                {
                    fscanf_s(pFile, "%d", &value);
                    (*data)[y][x] = value;
                }
            }

            fclose(pFile);
        }

        return data;
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
