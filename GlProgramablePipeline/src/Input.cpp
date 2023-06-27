#include "Input.h"

namespace Application
{
    static double previousX = 0.0;
    static double previousY = 0.0;
    static bool firstMouse = true;
    static double sensitivity = 0.1; 


	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
        switch (action)
        {
        case GLFW_PRESS:
            switch (key)
            {
            case KEY_ESCAPE:
                keys.escape = ACTION_PENDING;
                break;
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
            case KEY_UP:
                keys.up = DOWN;
                break;
            case KEY_DOWN:
                keys.down = DOWN;
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
            case KEY_UP:
                keys.up = UP;
                break;
            case KEY_DOWN:
                keys.down = UP;
                break;
            }
            break;
        }
	}
    void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            previousX = xpos;
            previousY = ypos;
            firstMouse = false;
        }

        xOffset = xpos - previousX;
        yOffset = previousY - ypos; 

        previousX = xpos;
        previousY = ypos;

        xOffset *= sensitivity;
        yOffset *= sensitivity;

        float min = 0.01f;

        if (xOffset < min && xOffset > 0 - min)
            xOffset = 0;
        if (yOffset < 0.01f && yOffset > 0- min)
            yOffset = 0;
    }
}
