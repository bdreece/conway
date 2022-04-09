#include <iostream>

#include <GL/gl.h>

#include "util.hpp"

namespace conway {
    void glClearError() {
        while (glGetError()) {
        }
    }

    bool glCheckError() {
        while (auto error = glGetError()) {
            std::cout << "[OpenGL Error] (" << std::hex << error << ")"
                      << std::endl;
            return false;
        }
        return true;
    }
} // namespace conway
