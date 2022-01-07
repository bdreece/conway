/**
 * @file        grid.cpp
 * @brief       Game of Life grid implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include "grid.hpp"

Grid::Grid(SDL_Window *window, int w, int h, int m, int n)
    : w(w), h(h), m(m), n(n) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  cells.reserve(n);

  for (int i = 0; i < cells.capacity(); i++) {
    cells.push_back(std::vector<SDL_Rect *>());
    cells[i].reserve(m);
    for (int j = 0; j < cells[i].capacity(); j++) {
      cells[i].push_back(new SDL_Rect{(int)(i * (w / m)), (int)(j * (h / n)),
                                      (int)(w / m), (int)(h / n)});
    }
  }
}

Grid::~Grid() {
  for (int i = 0; i < cells.size(); i++) {
    for (int j = 0; j < cells[i].size(); j++) {
      delete cells[i][j];
    }
  }

  SDL_DestroyRenderer(renderer);
}

void Grid::clear() { SDL_RenderClear(renderer); }

void Grid::updateCell(int row, int column, Cell status) {
  SDL_SetRenderDrawColor(renderer, (unsigned char)status, (unsigned char)status,
                         (unsigned char)status, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, cells[row][column]);
}

void Grid::flush() { SDL_RenderPresent(renderer); }
