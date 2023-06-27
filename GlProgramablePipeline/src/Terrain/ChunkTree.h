#pragma once
#include <memory>

#include "Chunk.h"

namespace Terrain
{
	class ChunkTree
	{
	public:
		ChunkTree(int x, int y);
		void Init();
		void AddChunk(int x, int y);
		void Render();
	private:
		int m_HeadX;
		int m_HeadY;
		std::vector<std::vector<std::shared_ptr<Chunk>>> m_Chunks;
		std::shared_ptr<Chunk> m_Head;
	protected:
		static int maxNodeDist;
	};
}