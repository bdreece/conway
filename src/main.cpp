/**
 * @file        main.cpp
 * @brief       Program execution and CLI
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "game.hpp"
#include "shader.hpp"

const char *const helpMessage =
    "Usage: ./conway WIN_SIZE CELL_SIZE SEED DELAY\n";

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
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

    // Use a doublebuffer
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Make window resizable by user
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    conway::Game *game = conway::Game::getInstance();

    // Create window with graphics context
    game->window = glfwCreateWindow(800, 600, "conway", NULL, NULL);
    if (game->window == NULL)
        return 1;
    glfwMakeContextCurrent(game->window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(game->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    game->init(400, 300, 69420, conway::Shader("", ""));

    while (!glfwWindowShouldClose(game->window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Something like this?
        game->loop();
    }
};
