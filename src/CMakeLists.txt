cmake_minimum_required(VERSION 3.25)
project(
    ag
    VERSION 0.0.1
    LANGUAGES CXX
)
include("./Defines.cmake")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
option(AG_USE_OPEN_GL "use OpenGL" OFF)
option(AG_USE_METAL "use Metal" OFF)
option(AG_USE_DIRECT_X "use DirectX" OFF)
if(AG_USE_OPEN_GL)
    if(WIN32)
        set(GLEW_ROOT "${EXTERNAL_DIR}/glew-2.1.0")
    endif()
    set(GLEW_USE_STATIC_LIBS ON)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
endif()
#
# Library Settings
#
if(WIN32)
    set(ENV{FREETYPE_DIR} "${EXTERNAL_DIR}/freetype-2.12.1")
endif()
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(FreeImage REQUIRED)
find_package(Freetype REQUIRED)
set(AG_INCLUDE
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${FREEIMAGE_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${ASSIMP_DIR}/include"
)
set(AG_LIBRARY
    ${GLFW_LIBRARIES}
    ${FREEIMAGE_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    "assimp"
)
if(AG_USE_OPEN_GL)
    list(APPEND AG_DEBUG_DEFINE AG_OPEN_GL)
    list(APPEND AG_RELEASE_DEFINE AG_OPEN_GL)
    list(APPEND AG_INCLUDE ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
    list(APPEND AG_LIBRARY ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
endif()
if(AG_USE_METAL)
    list(APPEND AG_DEBUG_DEFINE AG_METAL)
    list(APPEND AG_RELEASE_DEFINE AG_METAL)
    list(APPEND AG_LIBRARY "-framework Metal")
    list(APPEND AG_LIBRARY "-framework MetalKit")
    list(APPEND AG_LIBRARY "-framework Cocoa")
    list(APPEND AG_LIBRARY "-framework IOKit")
    list(APPEND AG_LIBRARY "-framework CoreVideo")
    list(APPEND AG_LIBRARY "-framework QuartzCore")
endif()
if(AG_USE_DIRECT_X)
    list(APPEND AG_DEBUG_DEFINE AG_DIRECT_X)
    list(APPEND AG_RELEASE_DEFINE AG_DIRECT_X)
    list(APPEND AG_LIBRARY "d3d12.lib")
    list(APPEND AG_LIBRARY "dxgi.lib")
endif()
if(NOT AG_USE_OPEN_GL AND NOT AG_USE_METAL AND NOT AG_USE_DIRECT_X)
    message(FATAL_ERROR "should select graphics driver.")
endif()
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