if(NOT WIN32)
    find_package(Freetype REQUIRED)
endif()

if (WIN32)
    set(FREETYPE_ROOTDIR "${EXTERNAL_DIR}/freetype-2.12.1" CACHE PATH "Root to FreeType directory")
endif()

# インクルードパスが空なら検索する
if(WIN32 OR (FREETYPE_FOUND AND (("${FREETYPE_INCLUDE_DIRS}" STREQUAL "") AND ("${GLEW_INCLUDE_DIR}" STREQUAL ""))))
    # for ft2build
    find_path(
        FREETYPE_INCLUDE_DIR_ft2build
        NAMES
            ft2build.h
        PATHS
            "${FREETYPE_ROOTDIR}/include"
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
            "${FREETYPE_ROOTDIR}/include/freetype"
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
            "${FREETYPE_ROOTDIR}/objs"
            "/usr/local/lib"
            "/opt/local/lib"
            "/opt/homebrew/lib"
    )
    set(FREETYPE_LIBRARIES "${FREETYPE_LIBRARIES}" CACHE PATH "FreeType Library")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeTypeEx DEFAULT_MSG FREETYPE_LIBRARIES FREETYPE_INCLUDE_DIRS)

mark_as_advanced(FREETYPE_INCLUDE_DIRS FREETYPE_LIBRARIES)
