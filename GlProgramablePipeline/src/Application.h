#pragma once
#include "Renderer.h"
#include "Renderable.h"

#include "GLFW/glfw3.h"

namespace Application
{
	extern Renderer::Renderer renderer;
	extern bool cursorLock;
	extern glm::vec3 cameraPosition;
	static std::vector <std::unique_ptr<Renderer::Renderable>> renderables;
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::mat4 model;
	static glm::mat4 mvpMatrix;
	
	static void Init();
	static void Render();
	static void ImGuiRender();
	static void Think();
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	glm::mat4 TranslateModel(const glm::vec3& translation);
}