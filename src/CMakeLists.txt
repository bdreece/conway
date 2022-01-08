find_package(OpenCL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(conway main.cpp grid.cpp game.cpp)
target_include_directories(conway PUBLIC ../inc)
target_link_libraries(conway OpenCL::OpenCL ${SDL2_LIBRARIES})
