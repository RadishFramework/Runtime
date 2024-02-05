#!/bin/bash -e

BUILD_TYPE="macos-release"

# If we're doing a CI build, then do a development build instead
if [ "$RADISH_CI_BUILD" == "1" ]; then
BUILD_TYPE="macos-development"
fi

cmake --preset $BUILD_TYPE $@
cmake --build --preset  $BUILD_TYPE --target RadishRuntime
cmake --install build/$BUILD_TYPE
