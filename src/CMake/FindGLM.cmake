# - FindGLM
#
# Author: Andre.Brodtkorb@sintef.no
#
# This module looks for the OpenGL Mathematics library
# It will define the following variable(s)
#  GLM_INCLUDE_DIRS = where glm/glm.hpp can be found

if (WIN32)
    set(GLM_ROOTDIR "${EXTERNAL_DIR}/glm" CACHE PATH "Root to GLM directory")
endif()

find_path(
	GLM_INCLUDE_DIR
	NAMES
		glm/glm.hpp
	PATHS
		"/opt/homebrew/include"
		"${GLM_ROOTDIR}"
)

if(NOT GLM_INCLUDE_DIR OR GLM_INCLUDE_DIR MATCHES "NOTFOUND")
	set(GLM_FOUND false)
	if(NOT GLM_QUIET)
		message( STATUS "GLM was not found")
	elseif(GLM_REQUIRED)
		message( SEND_ERROR "GLM was not found")
	endif()
else()
	set(GLM_FOUND true)
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

mark_as_advanced(GLM_INCLUDE_DIR)