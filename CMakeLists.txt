cmake_minimum_required(VERSION 3.25)
project(agTest CXX)

set(TEST_TEMPLATE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/tests/Template/Test.cmake")
set(TEST_TEMPLATE_MODS "${CMAKE_CURRENT_SOURCE_DIR}/tests/Template/CMake")
set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(ASSIMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodules/assimp")

enable_testing()
add_subdirectory(src)
add_subdirectory(submodules/assimp)

function(def_test label)
    add_subdirectory("tests/${label}")
    add_test("${label}" "tests/${label}/${label}")
endfunction()

def_test(Hello)
def_test(Window)
def_test(Image)
def_test(LowLevel)
def_test(Model)
def_test(TextureModel)