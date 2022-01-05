/**
 * @file        kernel.cpp
 * @brief       OpenCL kernel implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include "kernel.hpp"

Kernel::Kernel() {}

Kernel::~Kernel() {}

Kernel *Kernel::instance() { return nullptr; }

void Kernel::init() {}

void Kernel::compute() {}
