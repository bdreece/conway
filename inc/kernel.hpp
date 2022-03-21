/**
 * @file        game.hpp
 * @brief       Game of Life game class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/06/2022
 */

#include <vector>

#define CL_HPP_TARGET_OPENCL_VERSION 220
#include "CL/opencl.hpp"

namespace conway {
    class Kernel {
      public:
        Kernel(const int rows, const int cols);
        ~Kernel();

        void processCells(std::vector<unsigned char> &cells);

      private:
        void create(const std::vector<cl::Device> &devices);

        int cols, rows;
        cl::Context context;
        cl::CommandQueue queue;
        cl::Event event;
        cl::Kernel kernel;
        cl::Buffer inputCells;
        cl::Buffer outputCells;
    };
} // namespace conway
