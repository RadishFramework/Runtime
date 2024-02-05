include(CheckCXXSourceCompiles)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR "Clang")
    add_compile_options("-Wall -Wextra -Wno-unused")
endif()

check_cxx_source_compiles("
#include <source_location>
int main() { return 0; }
" RADISH_HAS_SOURCE_LOCATION)

if (RADISH_HAS_SOURCE_LOCATION)
    add_compile_definitions("RADISH_HAS_SOURCE_LOCATION")
endif()

add_subdirectory("radish")
add_subdirectory("runtime")
