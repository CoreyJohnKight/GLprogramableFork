#include "Player.h"
#include "Input.h"

namespace Player
{
	Player::Player()
		:m_position(0,20,500)
	{
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate()
	{
		float speed = 5.0f;
		if (Application::keys.forward == Application::KeystateEnum::DOWN)
		{
			m_position.z -= speed;
		}
		if (Application::keys.back == Application::KeystateEnum::DOWN)
		{
			m_position.z += speed;
		}
		if (Application::keys.left == Application::KeystateEnum::DOWN)
		{
			m_position.x -= speed;
		}
		if (Application::keys.right == Application::KeystateEnum::DOWN)
		{
			m_position.x += speed;
		}
	}

}
