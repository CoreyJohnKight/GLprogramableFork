#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"



#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Application.h"
#include "Texture.h"

#include "Renderable/Leroy.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


static void GLAPIENTRY glMsgCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cout << "GL LOG: type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 960, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    GLenum err = glewInit();
    
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 38.0f);
    //------------------------------------------------------------------
    glDebugMessageCallback(glMsgCallback, 0);
    //------------------------------------------------------------------

    // Init
    Application::Init();
   
  
    while (!glfwWindowShouldClose(window))
    {
        Application::renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Application::ImGuiRender();
        Application::Render();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        //std::cout << glGetError() << std::endl;
        Application::Think();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::Init()
{
    Application::renderer.Init();
    Application::projection = glm::ortho(0.0f, 1280.0f, 0.0f, 960.0f);
    Application::view = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));
    Application::model = glm::translate(glm::mat4(1.0f), glm::vec3(300, 200, 0));

    Application::mvpMatrix = Application::projection * Application::view * Application::model;
    
    renderables.push_back(std::make_unique<Renderable::Leroy>());
}


void Application::Render()
{
    //Leroy
    for (const auto& e : renderables)
    {
        e->OnRender();
    }
}

void Application::ImGuiRender()
{
    for (const auto& e : renderables)
    {
        e->OnImGuiRender();
    }
}

void Application::Think()
{
    for (const auto& e : renderables)
    {
        e->OnUpdate();
    }
}

void Application::TranslateModel(const glm::vec3& translation)
{
    Application::model = glm::translate(glm::mat4(1.0f), translation);
    Application::mvpMatrix = Application::projection * Application::view * Application::model;
}
