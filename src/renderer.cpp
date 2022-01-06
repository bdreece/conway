/**
 * @file        renderer.cpp
 * @brief       SDL2 renderer implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <cstdlib>

#include "renderer.hpp"
#include "util.hpp"

Renderer::Renderer(int width, int height, int m, int n, bool fullscreen) {
  const unsigned long flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  // Initialize SDL
  ASSERT(SDL_Init(SDL_INIT_VIDEO) >= 0);

  // Create window
  window = SDL_CreateWindow("conway", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640, 480, flags);
  ASSERT(window);

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  ASSERT(renderer);

  grid.reserve(m);
  // Construct grid (m: grid width, n: grid height)
  for (int i = 0; i < m; i++) {
    grid[i].reserve(n);

    for (int j = 0; j < n; j++) {
      grid[i][j].x = (int)(i * (width / m));
      grid[i][j].y = (int)(j * (height / n));
      grid[i][j].w = (int)(width / m);
      grid[i][j].h = (int)(height / n);
    }
  }
}

Renderer::~Renderer() { SDL_Quit(); }

void Renderer::startRenderLoop(long delay_ms) {
  bool is_quit = false;
  while (!is_quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
      if (e.type == SDL_QUIT) {
        is_quit = true;
        break;
      }

      SDL_RenderClear(renderer);

      // Compute aliveness matrix

      // Update rectangles
      updateRectangles();

      // Flush to screen
      SDL_RenderPresent(renderer);
      SDL_Delay(delay_ms);
    }
  }
}

void Renderer::updateRectangles() {}
