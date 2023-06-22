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
        if (firstMouse)
        {
            // Store the initial mouse position
            previousX = xpos;
            previousY = ypos;
            firstMouse = false;
        }

        // Calculate the offset between the current and previous mouse position
        xOffset = xpos - previousX;
        yOffset = previousY - ypos; 

        // Update the previous mouse position
        previousX = xpos;
        previousY = ypos;

        // Apply sensitivity factor to the offset for desired rotation speed
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        float min = 0.01f;

        if (xOffset < min && xOffset > 0 - min)
            xOffset = 0;
        if (yOffset < 0.01f && yOffset > 0- min)
            yOffset = 0;
    }
}
