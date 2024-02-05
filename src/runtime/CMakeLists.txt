set(Runtime_SRCS
"main.cpp"
)

add_executable(RadishRuntime WIN32 MACOSX_BUNDLE ${Runtime_SRCS})
target_link_libraries(RadishRuntime RadishFramework SDL2::SDL2main)
set_target_properties(RadishRuntime PROPERTIES
    INSTALL_RPATH "@executable_path/../Frameworks"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/macos/Info.plist.in"
    MACOSX_BUNDLE_ICON_FILE "radish.icns"
    MACOSX_BUNDLE_LONG_VERSION_STRING "${CMAKE_PROJECT_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${CMAKE_PROJECT_VERSION}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}"
    MACOSX_BUNDLE_BUNDLE_NAME "Radish Runtime"
    MACOSX_BUNDLE_COPYRIGHT "Copyright (c) Audrey Castillo. All rights reserved."
)

# We use hermesc to compile js code
add_dependencies(RadishRuntime hermesc)

install(TARGETS RadishRuntime DESTINATION .)

# Set up custom installation behaviour for macOS
if (APPLE)
    set(Runtime_LIBS_TO_FIX
        libhermes
        SDL2::SDL2
    )

    get_target_property(bundlePath RadishRuntime RUNTIME_OUTPUT_DIRECTORY)

    add_custom_command(TARGET RadishRuntime
        POST_BUILD 
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/macos/make-macos-icon.sh" "${CMAKE_CURRENT_SOURCE_DIR}/radish.svg" "${bundlePath}/RadishRuntime.app/Contents/Resources" "${CMAKE_CURRENT_BINARY_DIR}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    # Copy dylibs to Frameworks/
    foreach(_LIB ${Runtime_LIBS_TO_FIX})
        install(FILES "$<TARGET_FILE:${_LIB}>" DESTINATION "$<TARGET_FILE_BASE_NAME:RadishRuntime>.app/Contents/Frameworks")
    endforeach()

    # Copy the hermes compiler to the app bundle
    install(TARGETS hermesc DESTINATION "$<TARGET_FILE_BASE_NAME:RadishRuntime>.app/Contents/MacOS")

    # Codesign the bundle
    # TODO: use provided codesign credentials if available
    install(CODE "execute_process(COMMAND codesign -s \"-\" --deep $<TARGET_FILE_BASE_NAME:RadishRuntime>.app WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX})")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    configure_file("windows/radish.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/radish.rc" @ONLY)
    target_sources(RadishRuntime PRIVATE "windows/app.manifest" "${CMAKE_CURRENT_BINARY_DIR}/radish.rc")

    execute_process(COMMAND magick convert -background none "radish.svg" -resize 256x256 "${CMAKE_CURRENT_BINARY_DIR}/radish.ico"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

endif()
