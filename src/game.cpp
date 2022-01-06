/**
 * @file        game.cpp
 * @brief       Game of Life implementation
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/06/2022
 */

#include <fstream>
#include <sstream>

#include "game.hpp"
#include "util.hpp"

Game::Game(const std::string &kernelSourcePath, const int m, const int n)
    : m(m), n(n) {
  cl_int err;
  cl_device_type id;
  std::vector<cl::Device> devices;
  std::vector<cl::Platform> platforms;
  std::vector<cl_context_properties> contextProperties;

  // Get OpenCL platforms
  err = cl::Platform::get(&platforms);
  ASSERT(err == CL_SUCCESS, err);

  // Acquire context
  context = cl::Context(CL_DEVICE_TYPE_ALL, NULL, NULL, NULL, &err);
  ASSERT(err == CL_SUCCESS, err);

  // Get context properties
  contextProperties = context.getInfo<CL_CONTEXT_PROPERTIES>();
  ASSERT(contextProperties.size() != 0, 0);

  // Get context devices
  devices = context.getInfo<CL_CONTEXT_DEVICES>();
  ASSERT(devices.size() != 0, 0);

  // Select the GPU
  for (int i = 0; i < devices.size(); i++) {
    if (devices[i].getInfo<CL_DEVICE_TYPE>() == CL_DEVICE_TYPE_GPU)
      id = i;
  }

  // Prepare a command queue
  queue = cl::CommandQueue(context, devices[id], 0, &err);
  ASSERT(err == CL_SUCCESS, err);

  // Prepare input and output buffers
  inputCells =
      cl::Buffer(context, CL_MEM_READ_ONLY, m * n * sizeof(unsigned char));
  _m = cl::Buffer(context, CL_MEM_READ_ONLY, sizeof(int));
  _n = cl::Buffer(context, CL_MEM_READ_ONLY, sizeof(int));
  outputCells =
      cl::Buffer(context, CL_MEM_WRITE_ONLY, m * n * sizeof(unsigned char));

  createKernel(kernelSourcePath, devices);
}

Game::~Game() {
  queue.finish();
  queue.flush();
}

void Game::processCells(std::vector<unsigned char> &cells) {
  // Write buffer objects
  queue.enqueueWriteBuffer(inputCells, CL_TRUE, 0,
                           m * n * sizeof(unsigned char), cells.data(), NULL,
                           &event);
  event.wait();

  queue.enqueueWriteBuffer(_m, CL_TRUE, 0, sizeof(int), &m, NULL, &event);
  event.wait();

  queue.enqueueWriteBuffer(_n, CL_TRUE, 0, sizeof(int), &n, NULL, &event);
  event.wait();

  kernel.setArg(0, inputCells);
  kernel.setArg(1, _m);
  kernel.setArg(2, _n);
  kernel.setArg(3, outputCells);

  // Run kernel
  queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m * n),
                             cl::NDRange(1), NULL, &event);
  event.wait();

  // Read output buffer
  queue.enqueueReadBuffer(outputCells, CL_TRUE, 0,
                          m * n * sizeof(unsigned char), cells.data());
}

void Game::createKernel(const std::string &kernelSourcePath,
                        const std::vector<cl::Device> &devices) {
  cl_int err;
  cl::Program::Sources obj;
  cl::Program program;
  std::string kernelSource(
#include "conway.cl"
  );

  program = cl::Program(context, kernelSource, false, &err);
  ASSERT(err == CL_SUCCESS, err);

  program.build(devices);
  kernel = cl::Kernel(program, "process", &err);
  ASSERT(err == CL_SUCCESS, err);
}
