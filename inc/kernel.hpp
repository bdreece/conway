/**
 * @file        kernel.hpp
 * @brief       OpenCL kernel class
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/opencl.h>

class Kernel {
protected:
  Kernel();
  ~Kernel();
  void init();

public:
  static Kernel *instance();
  void compute();
};
