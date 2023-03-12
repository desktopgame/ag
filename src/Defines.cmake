# macro
set(AG_RELEASE_DEFINE AG_NDEBUG)
set(AG_DEBUG_DEFINE AG_DEBUG _DEBUG _LIBCPP_HAS_NO_ASAN) # https://stackoverflow.com/questions/38723374/why-does-xcode-define-libcpp-has-no-asan-when-creating-an-address-sanitized-bui
# compile options
set(AG_RELEASE_COMPILE -O3)
if (WIN32)
    set(AG_DEBUG_COMPILE -O0 -g -Wall -Werror -Wno-deprecated-declarations)
else()
    set(AG_DEBUG_COMPILE -O0 -g -Wall -Werror -Wno-deprecated-declarations -fsanitize=address)
endif()
# link options
if (WIN32)
    set(AG_DEBUG_LINK "")
else()
    set(AG_DEBUG_LINK -fsanitize=address)
endif()
set(AG_RELEASE_LINK "")