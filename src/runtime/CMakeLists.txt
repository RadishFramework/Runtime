set(Runtime_SRCS
"main.cpp"
)

add_executable(RadishRuntime WIN32 MACOSX_BUNDLE ${Runtime_SRCS})
target_link_libraries(RadishRuntime RadishFramework SDL2::SDL2main)
