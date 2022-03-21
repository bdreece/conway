#include <GL/glew.h>
#include <GL/gl.h>

#include "shader.hpp"

using namespace conway;

Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader) {
    unsigned int vertexId, fragmentId;

    id = glCreateProgram();
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    {
        const char *vertexData = vertexShader.data();
        const char *fragmentData = fragmentShader.data();

        glShaderSource(vertexId, vertexShader.size(), &vertexData, NULL);
        glShaderSource(fragmentId, fragmentShader.size(), &fragmentData, NULL);
    }

    glCompileShader(vertexId);
    glCompileShader(fragmentId);

    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);

    glLinkProgram(id);
}

const unsigned int Shader::getId() const { return id; }

const int Shader::getUniformLocation(const std::string &ident) const {
    return glGetUniformLocation(id, ident.data());
}
