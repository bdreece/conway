#include <string>

namespace conway {
    class Shader {
        unsigned int id;

      public:
        Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath);
        const unsigned int &get() const;
    };
} // namespace conway
