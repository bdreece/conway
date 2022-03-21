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
#include <thread>
#include <GL/glew.h>
#include <GL/gl.h>

#include "game.hpp"

using namespace conway;

Game::Game(int rows, int cols, unsigned int seed) {
    // Initialize grid and OpenCL kernel
    this->grid = std::make_unique<Grid>(rows, cols);
    this->kernel = std::make_unique<Kernel>(rows, cols);

    // Initialize cells per random seed
    cells.reserve(rows * cols);
    srand(seed);
    std::generate(cells.begin(), cells.end(),
                  []() { return rand() % 2 ? 0 : 255; });
}

void Game::loadShader(const std::string &name, const std::string &vertPath,
                      const std::string &fragPath) {
    std::stringstream vss{}, fss{};
    std::ifstream vfs(vertPath), ffs(fragPath);

    {
        std::string buf;
        while (vfs >> buf) {
            vss << buf;
        }
    }
    {
        std::string buf;
        while (ffs >> buf) {
            fss << buf;
        }
    }

    shaders[name] = std::make_shared<Shader>(vss.str(), fss.str());
}

void Game::loop() {
    grid->updateCells(cells);

    unsigned int liveCells = grid->liveCells();
    unsigned int deadCells = grid->deadCells();

    {
        auto shader = currentShader.lock();

        glUseProgram(shader->getId());
        glClearColor(0, 0, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, liveCells);
        glUniform4f(shader->getUniformLocation("color"), liveColor[0],
                    liveColor[1], liveColor[2], liveColor[3]);
        glDrawElements(GL_TRIANGLES, grid->numLiveCells(), GL_UNSIGNED_INT,
                       NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deadCells);
        glUniform4f(shader->getUniformLocation("color"), deadColor[0],
                    deadColor[1], deadColor[2], deadColor[3]);
        glDrawElements(GL_TRIANGLES, grid->numDeadCells(), GL_UNSIGNED_INT,
                       NULL);
    }
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
