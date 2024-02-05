#pragma once

#include "radish.hpp"

namespace radish {

enum class LogLevel {
    Info,
    Warn,
    Error,
};

constexpr static auto LogLevel_Strings = {
    "Info",
    "Warn",
    "Error",
};

namespace logging {

void printLine(bool toStdErr, std::string_view strData);

template<typename... TArgs>
void log(LogLevel level, radish::source_location location, fmt::format_string<TArgs...> format, TArgs&&... args) {
    auto str = fmt::format(format, std::forward<TArgs>(args)...);
    auto printData = fmt::format(
        "[{}] {} ({}:{})", 
        static_cast<size_t>(level) < LogLevel_Strings.size() ? LogLevel_Strings.begin()[static_cast<size_t>(level)] : "???", 
        str, 
        location.file_name(), 
        location.line()
    );

    printLine(level != LogLevel::Info, printData);
}

}

#define RADISH_LOG(level, ...) (radish::logging::log((level), SOURCE_LOC_HERE, __VA_ARGS__))

}