if(NOT WIN32)
    find_package(Freetype REQUIRED)
endif()

set(FREETYPEEX_VERSION "2.8.0.1")
set(FREETYPEEX_ROOTDIR "${NUGET_PACKAGEDIR}/freetype.${FREETYPEEX_VERSION}" CACHE PATH "Root to FreeType directory")

# インクルードパスが空なら検索する
if(WIN32 OR (FREETYPE_FOUND AND (("${FREETYPE_INCLUDE_DIRS}" STREQUAL "") AND ("${GLEW_INCLUDE_DIR}" STREQUAL ""))))
    # for ft2build
    find_path(
        FREETYPE_INCLUDE_DIR_ft2build
        NAMES
            ft2build.h
        PATHS
            "${FREETYPEEX_ROOTDIR}/build/native/include"
            "/usr/local/include"
            "/opt/local/include"
            "/opt/homebrew/include"
    )
    set(FREETYPE_INCLUDE_DIR_ft2build "${FREETYPE_INCLUDE_DIR_ft2build}" CACHE PATH "FreeType Include")
    # for freetype
    find_path(
        FREETYPE_INCLUDE_DIR_freetype2
        NAMES
            config/ftconfig.h
        PATHS
            "${FREETYPEEX_ROOTDIR}/build/native/include/freetype"
            "/usr/local/include"
            "/opt/local/include"
            "/opt/homebrew/include/freetype2/freetype"
            "/opt/homebrew/include"
    )
    set(FREETYPE_INCLUDE_DIR_freetype2 "${FREETYPE_INCLUDE_DIR_freetype2}" CACHE PATH "FreeType Include")
    set(FREETYPE_INCLUDE_DIRS "${FREETYPE_INCLUDE_DIR_ft2build};${FREETYPE_INCLUDE_DIR_freetype2}")
endif()
# ライブラリが空なら検索する
if(WIN32 OR (FREETYPE_FOUND AND (("${FREETYPE_LIBRARIES}" STREQUAL ""))))
    find_library(
        FREETYPE_LIBRARIES
        NAMES
            freetype28d
            freetype28
            freetype
        PATHS
            "${FREETYPEEX_ROOTDIR}/build/native/lib/Win32/v141/static/Debug"
            "/usr/local/lib"
            "/opt/local/lib"
            "/opt/homebrew/lib"
    )
    set(FREETYPE_LIBRARIES "${FREETYPE_LIBRARIES}" CACHE PATH "FreeType Library")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeTypeEx DEFAULT_MSG FREETYPE_LIBRARIES FREETYPE_INCLUDE_DIRS)

mark_as_advanced(FREETYPE_INCLUDE_DIRS FREETYPE_LIBRARIES)
