#include <chrono>
#include <spdlog/stopwatch.h>
#include "split.h"

void test_base() {
    spdlog::set_level(spdlog::level::info);
    spdlog::disable_backtrace();
    spdlog::stopwatch sw;
    for (int i = 0; i <= 4'000'000; ++i) {
        spdlog::debug("Logging message number {}", i);
    }
    spdlog::info("Spdlog elapsed: {:f} seconds", sw);
}


int main() {
    test_base();
    ::split::Split::test();
}