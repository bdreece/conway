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

const char *const helpMessage =
    "Usage: ./conway WIN_SIZE CELL_SIZE SEED DELAY\n";

int main(int argc, char **argv) {
  if (argc < 5) {
    std::cout << helpMessage << std::endl;
    return 1;
  }

  bool isOpen = true;
  int winSize, cellSize, n, total, err;
  unsigned int seed;
  unsigned long delay;
  std::vector<unsigned char> cells;

  winSize = std::stoi(argv[1]);
  cellSize = std::stoi(argv[2]);
  seed = std::stoul(argv[3]);
  delay = std::stoul(argv[4]);

  if (winSize <= 1) {
    std::cout << "Invalid WIN_SIZE" << std::endl;
    return 1;
  } else if (cellSize > winSize) {
    std::cout << "Invalid CELL_SIZE" << std::endl;
    return 1;
  }

  // Initialize SDL
  err = SDL_Init(SDL_INIT_VIDEO);
  ASSERT(err <= 0, err);
  SDL_Window *window =
      SDL_CreateWindow("conway", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       winSize, winSize, 0);
  ASSERT(window, 0);

  // Initialize grid and OpenCL kernel
  Grid grid(window, winSize, cellSize);
  total = grid.getTotal();
  n = grid.getN();

  Game game(n, n);

  // Initialize cells per random seed
  cells.reserve(total);
  srand(seed);
  for (int i = 0; i < total; i++) {
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
    for (int i = 0; i < total; i++) {
      grid.updateCell(i, cells[i] == 1 ? ALIVE : DEAD);
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
