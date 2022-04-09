/**
 *	@file		game.cpp
 *	@brief		Game computation and render loop
 *	@author		Brian Reece
 *	@version 	0.2.0
 *	@date		03/21/2022
 */

#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <GL/glew.h>
#include <GL/gl.h>

#include "game.hpp"
#include "util.hpp"

using namespace conway;

Game::Game(int rows, int cols, unsigned int seed) {
    // Initialize grid and OpenCL kernel
    this->grid = std::make_unique<Grid>(rows, cols);
    this->kernel = std::make_unique<Kernel>(rows, cols);

    // Load default shaders
    loadShader("default", "../inc/shaders/default.vert",
               "../inc/shaders/default.frag");
    setShader("default");

    // Initialize cells per random seed
    cells.reserve(rows * cols);
    srand(seed);
    std::generate(cells.begin(), cells.end(),
                  []() { return rand() % 2 ? 0 : 255; });
}

void Game::loadShader(const std::string &name, const std::string &vertPath,
                      const std::string &fragPath) {
    std::stringstream ss[2];
    std::ifstream vfs(vertPath), ffs(fragPath);

    std::string line;
    while (std::getline(vfs, line)) {
        ss[0] << line << "\n";
    }
    while (std::getline(ffs, line)) {
        ss[1] << line << "\n";
    }

    shaders[name] = std::make_shared<Shader>(ss[0].str(), ss[1].str());
}

void Game::loop() {
    grid->updateCells(cells);

    unsigned int liveCells = grid->liveCells();
    unsigned int deadCells = grid->deadCells();

    auto shader = currentShader.lock();

    GL_CALL(glUseProgram(shader->getId()));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, liveCells));
    GL_CALL(glUniform4f(shader->getUniformLocation("color"), liveColor[0],
                        liveColor[1], liveColor[2], liveColor[3]));
    GL_CALL(glDrawElements(GL_TRIANGLES, grid->numLiveCells() * 6,
                           GL_UNSIGNED_INT, nullptr));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deadCells));
    GL_CALL(glUniform4f(shader->getUniformLocation("color"), deadColor[0],
                        deadColor[1], deadColor[2], deadColor[3]));
    GL_CALL(glDrawElements(GL_TRIANGLES, grid->numDeadCells() * 6,
                           GL_UNSIGNED_INT, nullptr));
    GL_CALL(glFlush());

    kernel->processCells(cells);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void Game::setShader(const std::string &name) {
    if (shaders.contains(name)) {
        currentShader = shaders.at(name);
    }
}

const std::vector<std::string> Game::getShaders() const {
    std::vector<std::string> shaderNames{};
    shaderNames.reserve(shaders.size());
    std::transform(shaders.begin(), shaders.end(), shaderNames.begin(),
                   [](const auto &pair) { return pair.first; });
    return shaderNames;
}
