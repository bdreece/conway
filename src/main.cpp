#include <iostream>

#include "renderer.hpp"

int main() {
  Renderer renderer(640, 480, 20, 20, false);

  renderer.startRenderLoop(500);

  return 0;
}
