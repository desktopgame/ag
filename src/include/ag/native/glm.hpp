#pragma once

// このマクロ定義が必要。詳細は以下
// https://stackoverflow.com/questions/54930382/is-the-glm-math-library-compatible-with-apples-metal-shading-language
#if __APPLE__
#if AG_METAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE 1
#include <simd/simd.h>
#endif
#endif

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>