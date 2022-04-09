#include <GL/glew.h>
#include <GL/gl.h>
#include <cstring>

#include "shader.hpp"
#include "util.hpp"

using namespace conway;

Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader) {
    unsigned int vertexId, fragmentId;

    GL_CALL(id = glCreateProgram());
    GL_CALL(vertexId = glCreateShader(GL_VERTEX_SHADER));
    GL_CALL(fragmentId = glCreateShader(GL_FRAGMENT_SHADER));

    {
        const char *const vertexSource = vertexShader.c_str();
        const char *const fragmentSource = fragmentShader.c_str();
        GL_CALL(glShaderSource(vertexId, 1, &vertexSource, NULL));
        GL_CALL(glShaderSource(fragmentId, 1, &fragmentSource, NULL));
    }

    GL_CALL(glCompileShader(vertexId));
    GL_CALL(glCompileShader(fragmentId));

    GL_CALL(glAttachShader(id, vertexId));
    GL_CALL(glAttachShader(id, fragmentId));

    GL_CALL(glLinkProgram(id));
}

const unsigned int Shader::getId() const { return id; }

const int Shader::getUniformLocation(const std::string &ident) const {
    int location;
    GL_CALL(location = glGetUniformLocation(id, ident.data()));
    return location;
}
