#pragma once

#include "GLFW/glfw3.h"

#define KEY_ESCAPE GLFW_KEY_ESCAPE
#define KEY_FORWARD 'W'
#define KEY_BACK	'S'
#define KEY_LEFT	'A'
#define KEY_RIGHT	'D'
#define KEY_UP		GLFW_KEY_LEFT_SHIFT
#define KEY_DOWN	GLFW_KEY_SPACE

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
		KeystateEnum escape;
		KeystateEnum forward;
		KeystateEnum back;
		KeystateEnum left;
		KeystateEnum right;
		KeystateEnum up;
		KeystateEnum down;
	};

	inline double xOffset = 0.0;
	inline double yOffset = 0.0;

	inline KeyState keys =
	{
		.escape = UP,
		.forward = UP,
		.back = UP,
		.left = UP,
		.right = UP,
		.up = UP,
		.down = UP
	};

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos);
}