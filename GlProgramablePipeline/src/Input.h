#pragma once

#include "GLFW/glfw3.h"

#define KEY_FORWARD 'W'
#define KEY_BACK	'S'
#define KEY_LEFT	'A'
#define KEY_RIGHT	'D'

namespace Application
{
	enum KeystateEnum
	{
		DOWN = 0, 
		UP, 
		HELD, 
		ACTION_PENDING 
	};

	struct KeyState
	{
		KeystateEnum forward;
		KeystateEnum back;
		KeystateEnum left;
		KeystateEnum right;
	};

	extern KeyState keys;

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

}