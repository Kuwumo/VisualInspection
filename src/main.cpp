#include "inspection/inspection.hpp"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <array>
#include <cstdio>
#include <exception>
#include <memory>

namespace {
void run_demo() {
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console->set_level(spdlog::level::info);
    auto file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/inspection.log", 4096, 3);
    spdlog::logger inspection_log("inspection", {console, file});
    inspection_log.set_pattern("[%H:%M:%S.%e] [%n] [%^%l%$] %v");
    inspection_log.set_level(spdlog::level::trace);

    constexpr unsigned threshold = 80;
    constexpr std::array<unsigned, 3> scores{85, 79, 80};
    auto audit = spdlog::basic_logger_mt<spdlog::async_factory>(
        "audit", "logs/audit.log");
    inspection_log.info("Starting inspection: {} samples, threshold {}", scores.size(), threshold);
    unsigned sample = 0;
    unsigned passed = 0;
    for (unsigned score : scores) {
        ++sample;
        inspection_log.trace("Read sample {:03}", sample);
        inspection_log.debug("Sample {:03}: score={}, threshold={}", sample, score, threshold);
        const bool accepted = inspection::meets_threshold(score, threshold);
        if (accepted) {
            ++passed;
            inspection_log.info("Sample {:03}: PASS", sample);
        } else {
            inspection_log.warn("Sample {:03}: FAIL (score {})", sample, score);
        }
        audit->info("sample={:03} score={} accepted={}", sample, score, accepted);
    }
    inspection_log.info("Finished: {}/{} passed. Logs: logs/inspection.log and logs/audit.log",
                        passed, scores.size());
    inspection_log.flush();
    audit->flush();
}
}

int main() {
    try {
        run_demo();
    } catch (const std::exception& error) {
        std::fprintf(stderr, "Logging demo failed: %s\n", error.what());
        spdlog::shutdown();
        return 1;
    }
    spdlog::shutdown();
}
