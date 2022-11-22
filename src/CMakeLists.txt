cmake_minimum_required(VERSION 3.10)
project(
    ag
    VERSION 0.0.1
    LANGUAGES CXX
)
include("./Defines.cmake")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
option(AG_OPEN_GL "use OpenGL" ON)
if(AG_OPEN_GL)
    find_package(OpenGL REQUIRED)
endif()
#
# Library Settings
#
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(FreeImage REQUIRED)
set(AG_INCLUDE
    #${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${FREEIMAGE_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set(AG_LIBRARY
    #${OPENGL_LIBRARIES}
    "-framework Cocoa"
    "-framework Foundation"
    "-framework Metal"
    "-framework QuartzCore"
    ${GLFW_LIBRARIES}
    ${FREEIMAGE_LIBRARIES}
)
#
# Build Options
#
file(GLOB_RECURSE SOURCES "lib/*.cpp")
add_library(
    ag
    ${SOURCES}
)
target_compile_definitions(
    ag
    PRIVATE
    $<$<CONFIG:Release>:${AG_RELEASE_DEFINE}>
    $<$<CONFIG:Debug>:${AG_DEBUG_DEFINE}>
)
target_compile_options(
    ag
    PRIVATE
    $<$<CONFIG:Release>:${AG_RELEASE_COMPILE}>
    $<$<CONFIG:Debug>:${AG_DEBUG_COMPILE}>
)
target_link_options(
    ag
    PRIVATE
    $<$<CONFIG:Release>: ${AG_RELEASE_LINK}>
    $<$<CONFIG:Debug>: ${AG_DEBUG_LINK}>
)
target_compile_features(ag PRIVATE cxx_std_17)
target_include_directories(
    ag
    PRIVATE
    ${AG_INCLUDE}
)
target_link_libraries(
    ag
    PRIVATE
    ${AG_LIBRARY}
)