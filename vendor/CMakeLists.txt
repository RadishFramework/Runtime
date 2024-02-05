cmake_policy(SET CMP0077 NEW)

message(STATUS "-------- START VENDOR CONFIG -----------")

message(STATUS "-------- SDL2 -----------")
add_subdirectory("SDL")

set(SDL2_LIBRARIES SDL2::SDL2 PARENT_SCOPE)
set(SDL2_INCLUDE_DIRS "SDL/include")

message(STATUS "-------- fmt -----------")
set(FMT_INSTALL OFF)
add_subdirectory("fmt")

message(STATUS "-------- Hermes -----------")
set(HERMES_BUILD_APPLE_FRAMEWORK OFF)
add_subdirectory("hermes")

message(STATUS "-------- END VENDOR CONFIG -----------")
