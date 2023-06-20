#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <memory>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Renderer
{
	enum ShaderType
	{
		BASIC = 0
	};

	enum VaoType
	{
		VAO_BASIC_NO_TEXTURE = 0,
		VAO_BASIC
	};

	class Renderer
	{
	public:
		void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
		void Init();
		void Clear() const;
		std::weak_ptr<Shader> GetShader(ShaderType type);
		std::weak_ptr<VertexArray> GetVao(VaoType type);
	private:
		std::unordered_map<ShaderType, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<VaoType, std::shared_ptr<VertexArray>> m_VAOs;
	};
}