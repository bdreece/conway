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
#include <string>

#include "SDL.h"
#include "game.hpp"
#include "grid.hpp"
#include "util.hpp"

int main(int argc, char **argv) {
  if (argc < 7) {
    return 1;
  }

  bool isOpen = true;
  int w, h, m, n, seed, err;
  long delay;
  std::vector<unsigned char> cells;

  w = std::stoi(argv[1]);
  h = std::stoi(argv[2]);
  m = std::stoi(argv[3]);
  n = std::stoi(argv[4]);
  seed = std::stoi(argv[5]);
  delay = std::stol(argv[6]);

  // Initialize SDL
  err = SDL_Init(SDL_INIT_VIDEO);
  ASSERT(err <= 0, err);
  SDL_Window *window = SDL_CreateWindow("conway", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, w, h, 0);
  ASSERT(window, 0);

  // Initialize grid and OpenCL kernel
  Grid grid(window, w, h, m, n);
  Game game("../../inc/conway.cl", m, n);

  // Initialize cells per random seed
  cells.reserve(m * n);
  srand(seed);
  for (int i = 0; i < (m * n); i++) {
    cells[i] = rand() % 2 ? 0 : 1;
  }

  // Game loop
  while (isOpen) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isOpen = false;
        break;
      }
    }

    // Clear grid
    grid.clear();

    // Update grid with cells
    int k = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        grid.updateCell(i, j, (cells[k++] == 1) ? ALIVE : DEAD);
      }
    }

    // Flush grid
    grid.flush();

    // Advance game
    game.processCells(cells);
    SDL_Delay(delay);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
};
