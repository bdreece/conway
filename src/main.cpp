/**
 * @file        main.cpp
 * @brief       Program execution and CLI
 * @author      Brian Reece
 * @version     0.2.0
 * @date        03/21/2022
 */

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "game.hpp"

enum State {
    PLAY = 0,
    PAUSE = 1,
    STOP = 2,
};

const char *const helpMessage =
    "Usage: ./conway WIN_SIZE CELL_SIZE SEED DELAY\n";

static void glfw_error_callback(int error, const char *description) {
    std::cerr << "Glfw Error" << error << ": " << description << std::endl;
}

int main(int argc, char **argv) {

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

    State state = STOP;

    // Use a doublebuffer
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Make window resizable by user
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(800, 600, "conway", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (glewInit() != GLEW_OK)
        return 1;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    conway::Game game(400, 300, 69420);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0, 0, 0, 0);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("control");

            if (ImGui::Button("Play")) {
                state = PLAY;
            }

            if (ImGui::Button("Pause")) {
                state = PAUSE;
            }

            if (ImGui::Button("Stop")) {
                state = STOP;
            }

            ImGui::SliderInt("Delay (ms)", &game.delay, 0, 10000);
            ImGui::ColorPicker4("Live Color", game.liveColor.data());
            ImGui::ColorPicker4("Dead Color", game.deadColor.data());

            if (ImGui::TreeNode("Add Shader")) {
                std::string name, vertexPath, fragmentPath;
                ImGui::InputText("Name", name.data(), 64);
                ImGui::InputText("Vertex Shader", vertexPath.data(), 64);
                ImGui::InputText("Fragment Shader", fragmentPath.data(), 64);
                if (ImGui::Button("Compile")) {
                    game.loadShader(name, vertexPath, fragmentPath);
                }
            }

            ImGui::End();
        }

        ImGui::Render();

        // Something like this?
        if (state == PLAY) {
            game.loop();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
};
