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
#include "Input.h"

#include "Renderable/Leroy.h"
#include "Player/Player.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderable/Ground.h"
#include "Terrain/ChunkManager.h"
#include <Renderable/LightMain.h>


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

std::unique_ptr<Player::Player> player = std::make_unique<Player::Player>();
inline Renderer::Renderer Application::renderer = Renderer::Renderer();
std::unique_ptr<Terrain::ChunkManager> chunker = std::make_unique<Terrain::ChunkManager>(0,0);

static GLFWwindow* window;
inline bool Application::cursorLock = true;

int main(void)
{
    // Window (GLFW) Init
    //------------------------------------------------------------------

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // OpenGL (GLEW) Init
    //------------------------------------------------------------------
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    GLenum err = glewInit();
    
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    // ImGUI Init
    //------------------------------------------------------------------
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
    
    // Callbacks
    //------------------------------------------------------------------
    glfwSetFramebufferSizeCallback(window, Application::FramebufferSizeCallback);
    glDebugMessageCallback(glMsgCallback, 0);
    glfwSetKeyCallback(window, Application::KeyCallback);
    glfwSetCursorPosCallback(window, Application::MouseMovementCallback);
    
    // Application Init
    //------------------------------------------------------------------
    Application::Init();
   
  
    // Main Loop
    //------------------------------------------------------------------
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

        Application::Think();
    }

    // Shutdown
    //------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::Init()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    renderer.Init();
 
    chunker->m_ChunkTree->Init();
    Application::projection = glm::perspective(glm::radians(60.0f), 1280.0f / 960.0f, 1.0f, -1.0f);
    
    glm::vec3 cameraPosition(0.0f, 0.0f, 500.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    Application::view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    Application::model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Application::mvpMatrix = Application::projection * Application::view * Application::model;
    
    renderables.push_back(std::make_unique<Renderable::Leroy>(renderer.GetShader(Renderer::ShaderType::BASIC)));
    renderables.push_back(std::make_unique<Renderable::LightMain>(renderer.GetShader(Renderer::ShaderType::BASIC)));
    //renderables.push_back(std::make_unique<Renderable::Ground>(renderer.GetShader(Renderer::ShaderType::GROUND)));
}


void Application::Render()
{
    for (const auto& e : renderables)
    {
        e->OnRender();
    }
    chunker->m_ChunkTree->Render();
}

void Application::ImGuiRender()
{
    //TODO: TEMP
    ImGui::Begin("Debug");
    ImGui::SliderFloat3("LightPos", &(renderer.MainLightPos[0]), -10000.0f, 10000.0f);
    ImGui::End();
    for (const auto& e : renderables)
    {
        e->OnImGuiRender();
    }
}

void Application::Think()
{
    if (keys.escape == ACTION_PENDING)
    {
        cursorLock = !cursorLock;

        if(cursorLock)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        keys.escape = UP;
    }
    player->OnUpdate();
    glm::vec3 cameraPosition = player->GetPos();
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Apply rotation to camera position and target
    glm::vec3 rot = player->GetRot();
    float yaw = glm::radians(rot.y);
    float pitch = glm::radians(rot.x);
    glm::vec3 cameraDirection(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)
    );
    cameraDirection = glm::normalize(cameraDirection);

    cameraTarget = cameraPosition + cameraDirection;

    // Update view matrix based on camera position and target
    Application::view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    for (const auto& e : renderables)
    {
        e->OnUpdate();
    }
}

glm::mat4 Application::TranslateModel(const glm::vec3& translation)
{
    Application::model = glm::translate(glm::mat4(1.0f), translation);
    return Application::projection * Application::view * Application::model;
}

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Set the OpenGL viewport based on the new window size
    glViewport(0, 0, width, height);
}