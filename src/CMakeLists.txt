find_package(OpenCL REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(conway main.cpp)
target_include_directories(conway PUBLIC ../inc)
target_link_libraries(conway ${OpenCL_LIBRARY} ${SDL2_LIBRARIES})
