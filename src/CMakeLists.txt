cmake_minimum_required(VERSION 3.10)
project(
    ag
    VERSION 0.0.1
    LANGUAGES CXX
)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
#find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(FreeImage REQUIRED)

file(GLOB_RECURSE SOURCES "lib/*.cpp")
add_library(
    ag
    ${SOURCES}
)
target_compile_definitions(
    ag
    PRIVATE
    $<$<CONFIG:Release>:AG_NDEBUG>
    $<$<CONFIG:Debug>:AG_DEBUG _DEBUG>
)
target_compile_options(
    ag
    PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g -Wall -Werror -fsanitize=address>
)
target_link_options(
    ag
    PRIVATE
    $<$<CONFIG:Release>:>
    $<$<CONFIG:Debug>: -fsanitize=address>
)
target_compile_features(ag PRIVATE cxx_std_17)
target_include_directories(
    ag
    PRIVATE
    #${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${FREEIMAGE_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(
    ag
    PRIVATE
    #${OPENGL_LIBRARIES}
    "-framework Cocoa"
    "-framework Foundation"
    "-framework Metal"
    "-framework QuartzCore"
    ${GLFW_LIBRARIES}
    ${FREEIMAGE_LIBRARIES}
)