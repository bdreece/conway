#include <iostream>

#include "kernel.hpp"
#include "renderer.hpp"

int main() { 
  Kernel *kernel = Kernel::instance();
  Renderer *renderer = Renderer::instance();

  return 0;
}
