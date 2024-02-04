cmake_policy(SET CMP0077 NEW)

add_subdirectory("SDL")

set(SDL2_LIBRARIES SDL2::SDL2 PARENT_SCOPE)
set(SDL2_INCLUDE_DIRS "SDL/include")

set(FMT_INSTALL OFF)
add_subdirectory("fmt")

add_subdirectory("wasmtime")
