# For the app bundle we manually set the rpath
set(CMAKE_SKIP_BUILD_RPATH TRUE)

set(Runtime_SRCS
"main.cpp"
)

set(Runtime_LIBS_TO_FIX
libhermes
SDL2::SDL2
)

add_executable(RadishRuntime WIN32 MACOSX_BUNDLE ${Runtime_SRCS})
target_link_libraries(RadishRuntime RadishFramework SDL2::SDL2main)
set_target_properties(RadishRuntime PROPERTIES
    INSTALL_RPATH "@executable_path/../Frameworks"
)

# Building for macOS requires an annoying amount of app bundle setup.
# Do all that here.
if (false)
    foreach(_LIB ${Runtime_LIBS_TO_FIX})
        add_custom_command(TARGET RadishRuntime
            POST_BUILD COMMAND 
            ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${_LIB}>" "$<TARGET_FILE_DIR:RadishRuntime>/../Frameworks/$<TARGET_FILE_NAME:${_LIB}>"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endforeach()

    add_custom_command(TARGET RadishRuntime 
        POST_BUILD COMMAND 
        install_name_tool -add_rpath "@executable_path/../Frameworks/"
        "$<TARGET_FILE:RadishRuntime>"
    )

endif()