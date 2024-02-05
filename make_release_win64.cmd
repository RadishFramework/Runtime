@echo off

setlocal ENABLEDELAYEDEXPANSION

REM If we're doing a CI build, then do a development build instead
if %RADISH_CI_BUILD%=="1" (
    set BUILD_TYPE="win64-development"
) else (
    set BUILD_TYPE="win64-release"
)

cmake --preset %BUILD_TYPE% || exit 1
cmake --build --preset %BUILD_TYPE% --target RadishRuntime || exit 1
cmake --install build/%BUILD_TYPE% || exit 1
