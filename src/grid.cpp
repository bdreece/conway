/**
 * @file        grid.cpp
 * @brief       Game of Life grid implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include "grid.hpp"

Grid::Grid(SDL_Window *window, int winSize, int cellSize)
    : winSize(winSize), cellSize(cellSize) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  for (n = winSize / cellSize; n % cellSize != 0; n--) {
  }

  cells.reserve(n * n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cells.push_back(
          new SDL_Rect{i * cellSize, j * cellSize, cellSize, cellSize});
    }
  }
}

Grid::~Grid() {
  for (int i = 0; i < cells.size(); i++) {
    delete cells[i];
  }

  SDL_DestroyRenderer(renderer);
}

void Grid::clear() { SDL_RenderClear(renderer); }

void Grid::updateCell(int i, Cell status) {
  SDL_SetRenderDrawColor(renderer, (unsigned char)status, (unsigned char)status,
                         (unsigned char)status, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, cells[i]);
}

void Grid::flush() { SDL_RenderPresent(renderer); }

int Grid::getN() const { return n; }

int Grid::getTotal() const { return n * n; }
