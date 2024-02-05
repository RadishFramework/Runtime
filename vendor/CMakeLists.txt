cmake_policy(SET CMP0077 NEW)

# Sorry but this ain't my problem
if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR "Clang")
    add_compile_definitions("-Wno-deprecated-declarations")
endif()

message(STATUS "-------- START VENDOR CONFIG -----------")

message(STATUS "-------- SDL2 -----------")

# On macOS we build SDL2 ourselves (to get it as a universal binary)
if (APPLE OR ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_subdirectory("SDL")
    set(SDL2_LIBRARIES SDL2::SDL2 PARENT_SCOPE)
    set(SDL2_INCLUDE_DIRS "SDL/include")
else()
    find_package(SDL2 CONFIG REQUIRED)
endif()

message(STATUS "-------- fmt -----------")
option(FMT_INSTALL "" OFF)
add_subdirectory("fmt")

message(STATUS "-------- Hermes -----------")
option(HERMES_BUILD_APPLE_FRAMEWORK "" OFF)
add_subdirectory("hermes" EXCLUDE_FROM_ALL)

message(STATUS "-------- END VENDOR CONFIG -----------")
