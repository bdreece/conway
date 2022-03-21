/**
 * @file        grid.cpp
 * @brief       Game of Life grid implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <algorithm>
#include <numeric>
#include <cstddef>
#include <cstdlib>

#include <GL/glew.h>

#include "grid.hpp"

using namespace conway;

Grid::Grid(int rows, int cols) {
    // Generate GL buffers (1 vertex, 2 element)
    buffers.fill(0);
    glGenBuffers(3, buffers.data());

    // We are storing the coordinates of the vertices only
    {
        std::vector<double> vertices{};
        vertices.reserve(2 * (rows + 1) * (cols + 1));

        double offsets[2] = {
            2.0f * (1.0f / rows),
            2.0f * (1.0f / cols),
        };

        // Create static grid of vertices
        for (auto i = 0; i <= cols; i++) {
            for (auto j = 0; j <= rows; j++) {
                vertices.push_back(offsets[0] * i);
                vertices.push_back(offsets[1] * j);
            }
        }

        // Put vertices in GL array buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, 2 * (rows + 1) * (cols + 1),
                     vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    cells.reserve(rows * cols);
    for (unsigned int i = 0; i < (6 * rows * cols); i += 6) {
        cells.emplace_back(std::array<unsigned int, 6>{
            i + 1, i + cols + 1, i, i + cols + 1, i + cols, i});
    }
}

void Grid::updateCells(const std::vector<unsigned char> &cells) {
    std::vector<unsigned int> liveIndices{}, deadIndices{};
    live = dead = 0;
    {
        std::vector<std::array<unsigned int, 6>> liveCells{}, deadCells{};
        liveCells.reserve(
            std::count_if(cells.cbegin(), cells.cend(),
                          [](const auto &cell) { return cell > 0; }));
        liveIndices.reserve(6 * liveCells.capacity());
        deadCells.reserve(cells.size() - liveCells.capacity());
        deadIndices.reserve(6 * deadCells.capacity());

        auto cellIter = cells.cbegin();
        std::partition_copy(
            this->cells.cbegin(), this->cells.cend(), liveCells.begin(),
            deadCells.begin(),
            [&cellIter](const auto &val) { return *cellIter++ > 0; });

        for (const auto &cell : liveCells) {
            std::copy(cell.cbegin(), cell.cend(), liveIndices.end());
            live++;
        }

        for (const auto &cell : deadCells) {
            std::copy(cell.cbegin(), cell.cend(), deadIndices.end());
            dead++;
        }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, liveIndices.size(),
                 liveIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, deadIndices.size(),
                 deadIndices.data(), GL_STATIC_DRAW);
}

const unsigned int &Grid::deadCells() const { return buffers[2]; }

const std::size_t Grid::numDeadCells() const { return dead; }

const std::size_t Grid::numLiveCells() const { return live; }

const unsigned int &Grid::liveCells() const { return buffers[1]; }
