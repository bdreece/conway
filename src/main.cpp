#include <iostream>
#include <string>

#include "SDL.h"
#include "util.hpp"

int main(int argc, char **argv) {
  if (argc < 5) {
    return 1;
  }

  int w = std::stoi(argv[1]);
  int h = std::stoi(argv[2]);
  int m = std::stoi(argv[3]);
  int n = std::stoi(argv[4]);

  ASSERT(SDL_Init(SDL_INIT_VIDEO) <= 0);
  SDL_Window *window =
      SDL_CreateWindow("conway", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       w, h, 0);
  ASSERT(window);

  SDL_Delay(5000);

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
};
