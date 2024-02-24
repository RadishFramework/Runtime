project(QuickJS LANGUAGES C)

option(QUICKJS_ENABLE_BIGNUM "Enable BigNum support" ON)

set(QUICKJS_SRCS
"src/quickjs.c"
"src/libregexp.c"
"src/libunicode.c"
"src/cutils.c"
"src/quickjs-libc.c"
"src/libbf.c"
)

add_library(QuickJS STATIC ${QUICKJS_SRCS})

if (QUICKJS_ENABLE_BIGNUM)
    target_compile_definitions(QuickJS PUBLIC "CONFIG_BIGNUM=1")
endif()

file(READ "src/VERSION" QUICKJS_VERSION)

target_compile_definitions(QuickJS PRIVATE "CONFIG_VERSION=\"${QUICKJS_VERSION}\"")
target_link_directories(QuickJS PUBLIC "src")

if (${CMAKE_C_COMPILER_ID} MATCHES "Clang")
    target_compile_options(QuickJS PRIVATE
        "-Wall"
        "-Wextra"
        "-Wno-sign-compare"
        "-Wno-missing-field-initializers"
        "-Wundef"
        "-Wuninitialized"
        "-Wunused"
        "-Wno-unused-parameter"
        "-Wwrite-strings"
        "-Wchar-subscripts"
        "-funsigned-char"
    )
elseif (${CMAKE_C_COMPILER_ID} MATCHES "GCC")
    target_compile_options(QuickJS PRIVATE
        "-Wall"
        "-Wno-array-bounds"
        "-Wno-format-truncation"
    )
else()
endif()

if (NOT MSVC)
    target_compile_options(QuickJS PRIVATE "-fwrapv")
endif()

message(STATUS "BigNum support: ${QUICKJS_ENABLE_BIGNUM}")