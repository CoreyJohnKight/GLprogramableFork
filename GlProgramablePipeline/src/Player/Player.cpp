#include "Player.h"
#include "Input.h"
#include <iostream>
#include "Application.h"
namespace Player
{
	Player::Player()
		:m_Position(0,20,500), m_Rotation(0, 20, 500)
	{
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate()
	{
		float speed = 5.0f;
		glm::vec3 forward(
			cos(glm::radians(m_Rotation.y)),
			0.0f,
			sin(glm::radians(m_Rotation.y))
		);
		forward = glm::normalize(forward);

		glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));

		if (Application::keys.forward == Application::KeystateEnum::DOWN)
		{
			m_Position += forward * speed;
		}
		if (Application::keys.back == Application::KeystateEnum::DOWN)
		{
			m_Position -= forward * speed;
		}
		if (Application::keys.left == Application::KeystateEnum::DOWN)
		{
			m_Position -= right * speed;
		}
		if (Application::keys.right == Application::KeystateEnum::DOWN)
		{
			m_Position += right * speed;
		}

		if (Application::cursorLock)
		{
			// Update rotation based on mouse offset
			m_Rotation.y += Application::xOffset;
			m_Rotation.x += Application::yOffset;
			Application::xOffset = 0;
			Application::yOffset = 0;
		}

		// Clamp rotation to desired range if necessary
		// For example, if you want to keep the rotation within -180 to 180 degrees range:
		if (m_Rotation.x > 180.0f)
		{
			std::cout << "Clamping X" << std::endl;
			m_Rotation.x -= 360.0f;
		}
		else if (m_Rotation.x < -180.0f)
		{
			std::cout << "Clamping Y" << std::endl;
			m_Rotation.x += 360.0f;
		}
	}
}
