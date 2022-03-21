
#include <GL/glew.h>
#include <GL/gl.h>

#include "game.hpp"

using namespace conway;

Game *Game::getInstance() {
    if (!instance) {
        instance = std::make_unique<Game>();
    }

    return instance.get();
}

void Game::init(int rows, int cols, unsigned int seed, const Shader &shader) {
    // Initialize grid and OpenCL kernel
    grid = std::make_unique<Grid>(rows, cols);
    game = std::make_unique<Kernel>(rows, cols);
    this->shader = std::make_unique<Shader>(shader);

    // Initialize cells per random seed
    cells.reserve(400 * 300);
    srand(seed);
    for (int i = 0; i < cells.capacity(); i++) {
        cells[i] = rand() % 2 ? 0 : 255;
    }
}
void Game::loop() {
    grid->updateCells(cells);

    unsigned int liveCells = grid->liveCells();
    unsigned int deadCells = grid->deadCells();

    glUseProgram(shader->get());
    glClearColor(0, 0, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, liveCells);
    glUniform1i(0, 255);
    glDrawElements(GL_TRIANGLES, grid->numLiveCells(), GL_UNSIGNED_INT, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deadCells);
    glUniform1i(0, 0);
    glDrawElements(GL_TRIANGLES, grid->numDeadCells(), GL_UNSIGNED_INT, NULL);
}
