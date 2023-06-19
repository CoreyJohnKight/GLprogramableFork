#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Renderer
{
	class Renderer
	{
	private:

	public:
		void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shaderProg) const;
		void Init() const;
		void Clear() const;
	};
}