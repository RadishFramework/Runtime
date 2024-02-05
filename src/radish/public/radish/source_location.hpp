#pragma once

#include <cstdint>

#ifdef RADISH_HAS_SOURCE_LOCATION

#include <source_location>

namespace radish { 
using source_location = std::source_location;
}

#define SOURCE_LOC_HERE (std::source_location::current())

#else

namespace radish {

struct source_location {
    constexpr source_location(const char* file, const char* function, const uint32_t line, const uint32_t column) 
    : _file(file), 
    _function(function),
    _line(line),
    _column(column) {}

    [[nodiscard]]
    constexpr const char* file_name() const noexcept { return _file; }

    [[nodiscard]]
    constexpr const char* function_name() const noexcept { return _function; }

    [[nodiscard]]
    constexpr uint32_t line() const noexcept { return _line; }

    [[nodiscard]]
    constexpr uint32_t column() const noexcept { return _column; }

private:
    const char* _file{};
    const char* _function{};
    const uint32_t _line{};
    const uint32_t _column{};
};

#if defined(__GNUC__) || defined(__clang__)
#define SOURCE_LOC_HERE radish::source_location(__FILE__, __PRETTY_FUNCTION__, __LINE__, 1)
#elif defined(__MSC_VER)
#define SOURCE_LOC_HERE radish::source_location(__FILE__, __FUNCTION__, __LINE__, 1)
#else
#define SOURCE_LOC_HERE radish::source_location(__FILE__, __func__, __LINE__, 1})
#endif

}

#endif