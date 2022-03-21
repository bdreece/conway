#include <memory>

#include <GLFW/glfw3.h>

#include "grid.hpp"
#include "kernel.hpp"
#include "shader.hpp"

namespace conway {
    class Game {
        static std::unique_ptr<Game> instance;

      public:
        static Game *getInstance();
        void init(int rows, int cols, unsigned int seed, const Shader &shader);
        void loop();

        GLFWwindow *window;
        std::unique_ptr<Grid> grid;
        std::unique_ptr<Kernel> game;
        std::unique_ptr<Shader> shader;
        std::vector<unsigned char> cells;
        unsigned long delay;
    };

} // namespace conway
