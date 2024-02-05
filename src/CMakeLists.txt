set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR "Clang")
    add_compile_options("-Wall -Wextra -Wno-unused")
endif()

add_subdirectory("radish")
add_subdirectory("runtime")
