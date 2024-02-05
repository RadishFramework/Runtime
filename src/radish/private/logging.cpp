#include "radish/logging.hpp"

#include <cstdio>

namespace radish::logging {

void printLine(bool toStdErr, std::string_view strData) {
    auto* outLoc = toStdErr ? stderr : stdout;
    std::fputs(strData.data(), outLoc);
    std::fputc('\n', outLoc);
}

}