cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

# On apple we want to lookup where the xcode clang is from the command line.
if (APPLE)
    message(STATUS "Manually setting C/CXX compiler to Xcode version")
    execute_process(COMMAND "xcodebuild -find clang" OUTPUT_VARIABLE RADISH_XCODE_CLANG_PATH)
    execute_process(COMMAND "xcodebuild -find clang++" OUTPUT_VARIABLE RADISH_XCODE_CLANGPP_PATH)
    set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${RADISH_XCODE_CLANGPP_PATH})
endif()

project(RadishFramework VERSION 1.0.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

if (NOT DEFINED RADISH_ENABLE_ASSERTIONS)
    set(RADISH_ENABLE_ASSERTIONS OFF)
endif()

message(STATUS "*** Radish Configuration ***")
message(STATUS "* Assertions: ${RADISH_ENABLE_ASSERTIONS}")
message(STATUS "* LTO: ${CMAKE_INTERPROCEDURAL_OPTIMIZATION}")
message(STATUS "*** End Radish Configuration ***")

if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR "Clang")
    add_compile_options("-fno-rtti" "-fno-exceptions")
endif()

add_subdirectory("vendor")
add_subdirectory("src")
