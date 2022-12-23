cmake_minimum_required(VERSION 3.25)
project(${T_APP_NAME} CXX)

set(CMAKE_MODULE_PATH "${TEST_TEMPLATE_MODS}")

add_executable(${T_APP_NAME} main.cpp)
target_compile_definitions(
    ${T_APP_NAME}
    PRIVATE
    $<$<CONFIG:Release>:AG_TEST AG_NDEBUG>
    $<$<CONFIG:Debug>:AG_TEST AG_DEBUG _DEBUG>
)
if (WIN32)
    target_compile_options(
        ${T_APP_NAME}
        PRIVATE
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Debug>:-O0 -g -Wall -Werror -Wno-deprecated-declarations>
    )
    target_link_options(
        ${T_APP_NAME}
        PRIVATE
        $<$<CONFIG:Release>:>
        $<$<CONFIG:Debug>:>
    )
else()
    target_compile_options(
        ${T_APP_NAME}
        PRIVATE
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Debug>:-O0 -g -Wall -Werror -Wno-deprecated-declarations -fsanitize=address>
    )
    target_link_options(
        ${T_APP_NAME}
        PRIVATE
        $<$<CONFIG:Release>:>
        $<$<CONFIG:Debug>: -fsanitize=address>
    )
endif()
target_compile_features(${T_APP_NAME} PRIVATE cxx_std_17)
target_include_directories(
    ${T_APP_NAME}
    PRIVATE
    ${GLM_INCLUDE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/include"
)
target_link_libraries(
    ${T_APP_NAME}
    PRIVATE
    ag
)