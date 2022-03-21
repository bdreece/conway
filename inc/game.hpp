/**
 *	@file		game.hpp
 *	@brief		Game computation and render loop
 *	@author		Brian Reece
 *	@version	0.2.0
 *	@date		03/21/2022
 */

#include <array>
#include <map>
#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "grid.hpp"
#include "kernel.hpp"
#include "shader.hpp"

namespace conway {
    class Game {
        std::unique_ptr<Grid> grid;
        std::unique_ptr<Kernel> kernel;
        std::map<std::string, std::shared_ptr<Shader>> shaders;
        std::weak_ptr<Shader> currentShader;
        std::vector<unsigned char> cells;

      public:
        Game(int rows, int cols, unsigned int seed);

        void loop();

        void loadShader(const std::string &name, const std::string &vertPath,
                        const std::string &fragPath);
        void setShader(const std::string &name);
        const std::vector<std::string> getShaders() const;

        int delay;
        std::array<float, 4> liveColor, deadColor;
    };

} // namespace conway
