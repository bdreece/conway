#include "shader.hpp"

using namespace conway;

Shader::Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath) {}

const unsigned int &Shader::get() const { return id; }
