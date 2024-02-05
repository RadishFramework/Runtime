# Radish Framework

This repository consists of the C++ side of the Radish game framework. You might be looking for the NodeJS SDK instead.

## Building

Make sure to clone the repository with `--recursive` set.

### Windows

Some dependencies are required:
* `CMake`
* `Ninja`
* `vcpkg`, used for dependencies on Windows
* `ImageMagick`, optional (must have the convert command available). When not installed application icons will not build.

To just generate the binaries, run `make_release_win64.cmd`.

### MacOS

Some dependencies are required, all available through homebrew:
* `Xcode`, used instead of the system clang
* `cmake`
* `ninja`
* `imagemagick`, optional. When not installed application icons will not build.

To just generate the binaries, run `make_release_macos.sh`. This will create a Universal app.

### Linux

Haven't worked this part out yet.

Deps:
* `cmake`
* `ninja`
* `vcpkg`

Run `make_release_linux_<ARCH>.sh`, depending on Intel or ARM.

## License

Available under the MIT license.
