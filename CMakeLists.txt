cmake_minimum_required(VERSION 3.10)
project(agTest CXX)

set(TEST_TEMPLATE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/tests/Template/Test.cmake")
set(TEST_TEMPLATE_MODS "${CMAKE_CURRENT_SOURCE_DIR}/tests/Template/CMake")

enable_testing()
add_subdirectory(src)

function(def_test label)
    add_subdirectory("tests/${label}")
    add_test("${label}" "tests/${label}/${label}")
endfunction()

def_test(Hello)
def_test(Window)