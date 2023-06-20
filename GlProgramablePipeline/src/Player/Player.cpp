#include "Player.h"
#include "Input.h"
#include <iostream>

namespace Player
{
	Player::Player()
		:m_position(0,0,500)
	{
	}
	Player::~Player()
	{
	}
	void Player::OnUpdate()
	{
		float speed = 5.0f;
		//std::cout << Application::keys.forward << std::endl;
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
			m_position.x += speed;
		}
		if (Application::keys.right == Application::KeystateEnum::DOWN)
		{
			m_position.x -= speed;
		}
	}

}
