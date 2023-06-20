#pragma once

#include "../Renderable.h"
#include "glm/glm.hpp"

namespace Player
{
	class Player : public Renderer::Renderable
	{
	public:
		Player();
		~Player();
		void OnUpdate() override;

		inline const glm::vec3& GetPos() const {return m_position; }
	private:
		glm::vec3 m_position;

	};
}