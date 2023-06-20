#pragma once
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace Renderer
{
	class Renderable
	{
	public:
		Renderable() {}
		virtual ~Renderable() {}
	
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
}