if(NOT WIN32)
    # Windowsでないなら標準機能をまずは実行する
    find_package(GLEW REQUIRED)
endif()

# インクルードパスが空なら検索する
if(WIN32 OR (GLEW_FOUND AND (("${GLEW_INCLUDE_DIRS}" STREQUAL "") AND ("${GLEW_INCLUDE_DIR}" STREQUAL ""))))
    find_path(
        GLEW_INCLUDE_DIRS
        NAMES
            GL/glew.h
        PATHS
            "/usr/local/include"
            "/opt/local/include"
    )
    set(GLEW_INCLUDE_DIR "${GLEW_INCLUDE_DIRS}" CACHE PATH "GLEW Include")
    set(GLEW_INCLUDE_DIRS "${GLEW_INCLUDE_DIRS}" CACHE PATH "GLEW Include")
endif()
# ライブラリが空なら検索する
if(WIN32 OR (GLEW_FOUND AND (("${GLEW_LIBRARIES}" STREQUAL "") AND ("${GLEW_LIBRARY}" STREQUAL ""))))
    find_library(
        GLEW_LIBRARY
        NAMES
            GLEW
            glew
            glew32
            glew32s
        PATHS
            "/usr/local/lib"
            "/opt/local/lib"
    )
    set(GLEW_LIBRARIES "${GLEW_LIBRARY}" CACHE PATH "GLEW Library")
    set(GLEW_LIBRARY "${GLEW_LIBRARY}" CACHE PATH "GLEW Library")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEWEx DEFAULT_MSG GLEW_LIBRARIES GLEW_INCLUDE_DIR)

mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARIES)
mark_as_advanced(GLEW_INCLUDE_DIRS GLEW_LIBRARY)
