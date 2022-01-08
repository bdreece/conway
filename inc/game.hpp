/**
 * @file        game.hpp
 * @brief       Game of Life game class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/06/2022
 */

#include <vector>

#define CL_HPP_TARGET_OPENCL_VERSION 300
#include "CL/opencl.hpp"

class Game {
public:
  Game(const int m, const int n);
  ~Game();

  void processCells(std::vector<unsigned char> &cells);

private:
  void createKernel(const std::vector<cl::Device> &devices);

  int cols, rows;
  cl::Context context;
  cl::CommandQueue queue;
  cl::Event event;
  cl::Kernel kernel;
  cl::Buffer inputCells;
  cl::Buffer outputCells;
};
