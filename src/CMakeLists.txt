find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
# link_libraries(OpenCL::OpenCL)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
# link_libraries(OpenGL::OpenGL)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
# link_libraries(GLEW::GLEW)

find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
# link_libraries(glfw)

set(IMGUI_DIR ../lib/imgui)

add_library(conway_s grid.cpp game.cpp kernel.cpp shader.cpp)
target_include_directories(conway_s PUBLIC ../inc)
target_link_libraries(conway_s OpenCL::OpenCL OpenGL::OpenGL GLEW::GLEW glfw)

add_executable(
  conway
  main.cpp
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
target_include_directories(conway PUBLIC ../inc ${IMGUI_DIR})
target_link_libraries(conway conway_s)
