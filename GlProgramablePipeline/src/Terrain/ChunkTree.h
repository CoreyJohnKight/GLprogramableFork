#pragma once

namespace Terrain
{
	class ChunkTree
	{
	public:
		ChunkTree(int x, int y);
		void AddChunk(int x, int y);
	private:
		int m_HeadX;
		int m_HeadY;
	};
}