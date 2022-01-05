/**
 * @file        renderer.hpp
 * @brief       SDL2 renderer class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include "SDL2/SDL.h"

class Renderer {
protected:
  Renderer();
  ~Renderer();
  void init();

public:
  static Renderer *instance();
  void render();
};
