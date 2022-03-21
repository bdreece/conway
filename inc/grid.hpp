/**
 * @file        grid.hpp
 * @brief       Game of Life grid class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <array>
#include <vector>

namespace conway {
    class Grid {
      public:
        Grid(int rows, int cols);

        void updateCells(const std::vector<unsigned char> &cells);
        const unsigned int &deadCells() const;
        const std::size_t numDeadCells() const;
        const unsigned int &liveCells() const;
        const std::size_t numLiveCells() const;

      private:
        std::vector<std::array<unsigned int, 6>> cells;
        std::size_t live, dead;
        std::array<unsigned int, 3> buffers;
    };
} // namespace conway
