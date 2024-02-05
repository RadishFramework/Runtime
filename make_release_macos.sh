#!/bin/bash

echo "Making macOS Universal Release"
cmake --preset macos-release .
cmake --build --preset macos-release --target RadishRuntime .
cmake --install .
