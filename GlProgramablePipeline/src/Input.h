#pragma once

#include "GLFW/glfw3.h"

#define KEY_FORWARD 'W'
#define KEY_BACK	'S'
#define KEY_LEFT	'A'
#define KEY_RIGHT	'D'

#pragma once

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

	inline double xOffset = 0.0;
	inline double yOffset = 0.0;

	inline KeyState keys =
	{
		.forward = UP,
		.back = UP,
		.left = UP,
		.right = UP
	};

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos);
}