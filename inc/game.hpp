/**
 * @file        game.hpp
 * @brief       Game of Life game class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/06/2022
 */

#include <vector>

#include "CL/opencl.hpp"

class Game {
public:
  Game(const std::string &kernelSourcePath, const int m, const int n);
  ~Game();

  void processCells(std::vector<unsigned char> &cells);

private:
  void createKernel(const std::string &kernelSourcePath,
                    const std::vector<cl::Device> &devices);

  int m, n;
  cl::Context context;
  cl::CommandQueue queue;
  cl::Event event;
  cl::Kernel kernel;
  cl::Buffer inputCells;
  cl::Buffer outputCells;
};