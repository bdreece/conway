/**
 * @file        util.hpp
 * @brief       Utility functions and macros
 * @author      Brian Reece
 * @version     0.1.0
 * @date        01/05/2022
 */

#include <GL/gl.h>
#include <errno.h>
#include <error.h>

#define ASSERT(x, s)                                                           \
    do {                                                                       \
        if (!(x))                                                              \
            error_at_line(1, errno, __FILE__, __LINE__, "(%s)", s);            \
    } while (0)

#define GL_CALL(x)                                                             \
    glClearError();                                                            \
    x;                                                                         \
    ASSERT(glCheckError(), #x);

namespace conway {
    void glClearError();
    bool glCheckError();
} // namespace conway
