#include <chrono>
#include <spdlog/stopwatch.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "split.h"

namespace split {
std::string Split::lvl2string(const spdlog::level::level_enum lvl) {
    switch (lvl) {
        case spdlog::level::trace:
            return "trace";
        case spdlog::level::debug:
            return "debug";
        case spdlog::level::info:
            return "info";
        case spdlog::level::warn:
            return "warn";
        case spdlog::level::err:
            return "error";
        case spdlog::level::critical:
            return "critical";
        default:
            return "";
    }
}


void Split::test() {
    SCOPE()
    const std::vector<spdlog::level::level_enum> allPrintLevels{
            spdlog::level::trace, spdlog::level::debug, spdlog::level::info,
            spdlog::level::warn, spdlog::level::err, spdlog::level::critical
    };
    spdlog::set_automatic_registration(true);
    for (const auto level : allPrintLevels) {
        const auto spdLogger{spdlog::stdout_color_mt(lvl2string(level))};
        spdLogger->set_level(level);
        spdLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    }

    spdlog::stopwatch sw;
    for (int i = 0; i <= 4'000'000; ++i) {
        BASE_PRINTDBG("Logging message number {}", i);
    }
    BASE_PRINT("Split loggers elapsed: {:f} seconds", sw);
}
}
