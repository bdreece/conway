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

  cells.reserve(m);

  for (int i = 0; i < m; i++) {
    cells.push_back(std::vector<SDL_Rect *>());
    cells[i].reserve(n);
    for (int j = 0; j < n; j++) {
      cells[i].push_back(new SDL_Rect{(int)(i * (w / m)), (int)(j * (h / n)),
                                      (int)(w / m), (int)(h / n)});
    }
  }
}

Grid::~Grid() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      delete cells[i][j];
    }
  }

  SDL_DestroyRenderer(renderer);
}

void Grid::clear() { SDL_RenderClear(renderer); }

void Grid::updateCell(int x, int y, Cell status) {
  SDL_SetRenderDrawColor(renderer, status, status, status, 255);
  SDL_RenderFillRect(renderer, cells[x][y]);
}

void Grid::flush() { SDL_RenderPresent(renderer); }
