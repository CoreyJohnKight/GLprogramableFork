#pragma once
#include <memory>
#include <vector>
namespace Terrain
{
	class Chunk
	{
	public:
		Chunk(int x, int y);
		const int m_X;
		const int m_Y;
		std::unique_ptr<std::vector<std::vector<int>>> m_ChunkData;
	private:
	};
}