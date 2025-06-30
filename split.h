#ifndef SPLIT_H
#define SPLIT_H
#include <string>

#include <spdlog/spdlog.h>
#define SCOPE(name)               \
    const std::string fns(#name); \
    spdlog::level::level_enum lpl = spdlog::level::info; \
    split::Split::PRINT(spdlog::level::trace, fns);

#define BASE_PRINT(...) if (lpl <= spdlog::level::info)  split::Split::PRINT(spdlog::level::info, __VA_ARGS__);
#define BASE_PRINTDBG(...) if (lpl <= spdlog::level::debug)  split::Split::PRINT(spdlog::level::debug, __VA_ARGS__);

namespace split {
class Split {
public:
    static void test();
    static std::string lvl2string(spdlog::level::level_enum lvl);

    template <typename FormatString, typename... Args>
    static void PRINT(spdlog::level::level_enum lvl, const FormatString& fmt, Args&&... args);
};


template <typename FormatString, typename... Args>
void Split::PRINT(const spdlog::level::level_enum lvl, const FormatString& fmt, Args&&... args) {
    const auto loggerName{lvl2string(lvl)};
    const auto spdLogger{spdlog::get(loggerName)};
    if (spdLogger != nullptr) {
        auto buf = fmt::memory_buffer();
        fmt::vformat_to(std::back_inserter(buf), fmt, fmt::make_format_args(args...));
        spdLogger->log(lvl, {buf.data(), buf.size()});
    }
}
} // namespace split
#endif //SPLIT_H