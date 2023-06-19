#pragma once
#include <vector>
#include <GL/glew.h>
#include <assert.h>

namespace Renderer
{
	struct VertexLayoutElement
	{
		GLuint type;
		GLuint count;
		GLboolean normalized;

		static GLuint GetTypeSize(GLuint type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;

			assert(false);
			default: return 0;
			}
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexLayoutElement> m_Elements;
		GLuint m_Stride;

	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		template<typename T>
		void PushElement(GLuint count, GLboolean normalized)
		{
			assert(false);
		}

		template<>
		void PushElement<GLfloat>(GLuint count, GLboolean normalized)
		{
			m_Elements.push_back({GL_FLOAT, count, normalized});
			m_Stride += VertexLayoutElement::GetTypeSize(GL_FLOAT) * count;
		}

		template<>
		void PushElement<GLuint>(GLuint count, GLboolean normalized)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, normalized });
			m_Stride += VertexLayoutElement::GetTypeSize(GL_UNSIGNED_INT) * count;
		}

		template<>
		void PushElement<GLbyte>(GLuint count, GLboolean normalized)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, normalized });
			m_Stride += VertexLayoutElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
		}

		inline std::vector<VertexLayoutElement> GetElements() const { return m_Elements; }
		inline GLuint GetStride() const { return m_Stride; }

	};	
}