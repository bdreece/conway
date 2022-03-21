#include <string>

namespace conway {
    class Shader {
        unsigned int id;

      public:
        Shader(const std::string &vertexShader,
               const std::string &fragmentShader);
        const unsigned int getId() const;
        const int getUniformLocation(const std::string &ident) const;
    };
} // namespace conway
