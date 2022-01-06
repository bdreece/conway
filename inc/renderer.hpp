/**
 * @file        renderer.hpp
 * @brief       SDL2 renderer class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <memory>
#include <vector>

#include "SDL2/SDL.h"

#include "kernel.hpp"

class Renderer {
public:
  Renderer(int width, int height, int m, int n, bool fullscreen);
  ~Renderer();
  void startRenderLoop(long delay_ms);

private:
  void updateRectangles();

  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<std::vector<SDL_Rect>> grid; // x by y
};
