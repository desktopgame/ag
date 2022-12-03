# macro
set(AG_RELEASE_DEFINE AG_NDEBUG)
set(AG_DEBUG_DEFINE AG_DEBUG _DEBUG)
# compile options
set(AG_RELEASE_COMPILE -O3)
set(AG_DEBUG_COMPILE -O0 -g -Wall -Werror -Wno-deprecated-declarations -fsanitize=address)
# link options
set(AG_RELEASE_LINK "")
set(AG_DEBUG_LINK -fsanitize=address)