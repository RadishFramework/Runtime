set(Radish_Public_SRCS
"public/radish.hpp"
"public/radish/application.hpp"
"public/radish/error.hpp"
"public/radish/source_location.hpp"
"public/radish/type_id.hpp"
"public/radish/vm.hpp"
)

set(Radish_Private_SRCS
"private/application.cpp"
"private/vm.cpp"
)

set(Radish_HERMES_LIBS
libhermes
jsi
)

add_library(RadishFramework STATIC ${Radish_Public_SRCS} ${Radish_Private_SRCS})
target_include_directories(RadishFramework PUBLIC "public" ${SDL2_INCLUDE_DIRS} PRIVATE "private")
target_link_libraries(RadishFramework ${SDL2_LIBRARIES} fmt::fmt ${Radish_HERMES_LIBS})

if (UNIX)
    target_link_libraries(RadishFramework "m")
endif()
