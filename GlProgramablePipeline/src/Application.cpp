#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"


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

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
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
    Renderer::Renderer renderer;
    renderer.Init();

    Renderer::Shader shader("Resources/Shaders/BasicVert.glsl", "Resources/Shaders/BasicFrag.glsl");
    shader.Bind();

    glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(300, 200, 0));
    glm::mat4 mvp = projection * view * model;
    
    shader.SetUniformMat4f("u_MVP", mvp);


    GLfloat triPos[] = {
         100.0f,   100.0f, 0.0f, 0.0f,
         200.0f,   100.0f, 1.0f, 0.0f,
         200.0f,   200.0f, 1.0f, 1.0f,
         100.0f,   200.0f, 0.0f, 1.0f,
    };

    GLuint indicies[] = {
        0, 1, 2,
        2, 3, 0
    };
    

    Renderer::VertexArray va;
    Renderer::VertexBuffer vb(triPos, 4 * 4 * sizeof(GLfloat));

    Renderer::VertexBufferLayout layout;
    layout.PushElement<GLfloat>(2, GL_FALSE);
    layout.PushElement<GLfloat>(2, GL_FALSE);
    va.AttatchVertexBuffer(vb, layout);

    Renderer::IndexBuffer ib(indicies, 6);

    shader.SetUniform4f("u_Colour", 0.0f, 0.0f, 0.0f, 0.0f);

    Renderer::Texture tex("Resources/Textures/Leroy.png");
    tex.Bind();
    shader.SetUniform1i("u_Texture", 0);

    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    GLfloat a = 0.0f;
    GLfloat rIncrement = 0.05f;
    GLfloat gIncrement = 0.05f;
    GLfloat bIncrement = 0.05f;
    glm::vec3 tanslation(300, 200, 0);
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        //ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Text("Application average %.3f ms/frame (%.1f fps)", 1000 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::SliderFloat3("Transform", &tanslation.x, 0.0f, 640.0f);

        if (r > 1.0f)
            rIncrement = -0.004f;
        else if( r < 0.3f)
            rIncrement = 0.005f;
        r += rIncrement;

        if (g > 1.0f)
            gIncrement = -0.006f;
        else if (r < 0.3f)
            gIncrement = 0.006f;
        g += gIncrement;

        if (b > 1.0f)
            bIncrement = -0.004f;
        else if (b < 0.3f)
            bIncrement = 0.004f;
        b += bIncrement;

        shader.SetUniform4f("u_Colour", r,g,b, 1.0f);

        model = glm::translate(glm::mat4(1.0f), tanslation);
        mvp = projection * view * model;

        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(va, ib, shader);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
