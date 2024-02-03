set(Radish_Public_SRCS
"public/radish.hpp"
"public/radish/error.hpp"
"public/radish/application.hpp"
)

set(Radish_Private_SRCS
"private/application.cpp"
)

add_library(RadishFramework STATIC ${Radish_Public_SRCS} ${Radish_Private_SRCS})
target_include_directories(RadishFramework PUBLIC "public" ${SDL2_INCLUDE_DIRS} PRIVATE "private")
target_link_libraries(RadishFramework ${SDL2_LIBRARIES} fmt::fmt)

if (UNIX)
    target_link_libraries(RadishFramework "m")
endif()
