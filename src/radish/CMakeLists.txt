set(Radish_Public_SRCS
"public/radish.hpp"
)

set(Radish_Private_SRCS
"private/test.cpp"
)

add_library(RadishFramework STATIC ${Radish_Public_SRCS} ${Radish_Private_SRCS})
target_include_directories(RadishFramework PUBLIC "public" ${SDL2_INCLUDE_DIRS} PRIVATE "private")
target_link_libraries(RadishFramework PUBLIC ${SDL2_LIBRARIES})
