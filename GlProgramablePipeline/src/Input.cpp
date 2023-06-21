#include "Input.h"

namespace Application
{
    inline KeyState keys =
    {
        .forward = UP,
        .back = UP,
        .left = UP,
        .right = UP
    };

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
        switch (action)
        {
        case GLFW_PRESS:
            switch (key)
            {
            case KEY_FORWARD:
                keys.forward = DOWN;
                break;
            case KEY_BACK:
                keys.back = DOWN;
                break;
            case KEY_LEFT:
                keys.left = DOWN;
                break;
            case KEY_RIGHT:
                keys.right = DOWN;
                break;
            }
            break;
        case GLFW_RELEASE:
            switch (key)
            {
            case KEY_FORWARD:
                keys.forward = UP;
                break;
            case KEY_BACK:
                keys.back = UP;
                break;
            case KEY_LEFT:
                keys.left = UP;
                break;
            case KEY_RIGHT:
                keys.right = UP;
                break;
            }
            break;
        }
	}
    void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
    {
        //TODO
    }
}
