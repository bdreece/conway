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
  Grid(SDL_Window *window, int winSize, int cellSize);
  ~Grid();

  void clear();
  void updateCell(int i, Cell status);
  void flush();
  int getN() const;
  int getTotal() const;

private:
  SDL_Renderer *renderer;
  std::vector<SDL_Rect *> cells;
  int winSize, cellSize, n;
};
