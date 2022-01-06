/**
 * @file        util.hpp
 * @brief       Utility functions and macros
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <errno.h>
#include <error.h>

#define ASSERT(x, y)                                                           \
  do {                                                                         \
    if (!(x))                                                                  \
      error_at_line(1, errno, __FILE__, __LINE__, "(%s): %d", #x, y);          \
  } while (0)
