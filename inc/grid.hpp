/**
 * @file        grid.hpp
 * @brief       Game of Life grid class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <vector>

#include "SDL.h"

enum Cell : unsigned char { DEAD = 0, ALIVE = 255 };

class Grid {
public:
  Grid(SDL_Window *window, int w, int h, int m, int n);
  ~Grid();

  void clear();
  void updateCell(int x, int y, Cell status);
  void flush();

private:
  SDL_Renderer *renderer;
  std::vector<std::vector<SDL_Rect *>> cells;
  int w, h, m, n;
};
