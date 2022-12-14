if (WIN32)
    set(FREEIMAGE_ROOTDIR "${EXTERNAL_DIR}/FreeImage" CACHE PATH "Root to FreeImage directory")
    set(FREEIMAGE_INCLUDE_ROOTDIR "${EXTERNAL_DIR}/FreeImage3180" CACHE PATH "Root to FreeImage include directory")
endif()

find_path(
    FREEIMAGE_INCLUDE_DIR
    NAMES
        FreeImage.h
    PATHS
        "/usr/local/include"
        "/opt/local/include"
        "/opt/homebrew/include"
        "${FREEIMAGE_INCLUDE_ROOTDIR}/FreeImage/Source"
)

set(FREEIMAGE_NAMES FREEIMAGE freeimage)
find_library(
    FREEIMAGE_LIBRARY
    NAMES
        ${FREEIMAGE_NAMES}
    PATHS
        "/usr/local/lib"
        "/opt/local/lib"
        "/opt/homebrew/lib"
        "${FREEIMAGE_ROOTDIR}/Dist/x64"
)
mark_as_advanced( FREEIMAGE_LIBRARY FREEIMAGE_INCLUDE_DIR )

# Per-recommendation
set(FREEIMAGE_INCLUDE_DIRS "${FREEIMAGE_INCLUDE_DIR}")
set(FREEIMAGE_LIBRARIES    "${FREEIMAGE_LIBRARY}")

if(NOT FREEIMAGE_INCLUDE_DIRS OR FREEIMAGE_INCLUDE_DIRS MATCHES "NOTFOUND")
    set(FREEIMAGE_FOUND false)
else()
    set(FREEIMAGE_FOUND true)
endif()
