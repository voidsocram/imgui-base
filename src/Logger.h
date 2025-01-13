#pragma once
#define FMT_HEADER_ONLY         
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Windows.h>
#include <iostream>

class Logger {
public:
    static void Init();
    static void Shutdown();
    static void AttachConsole();
    static void DetachConsole();
    static void HideConsole();
    static void ShowConsole();
    static bool IsConsoleVisible();
    static void ToggleConsole();

    template<typename... Args>
    static void TRACE(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        Log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void INFO(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        Log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void WARN(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        Log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void ERR(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        Log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void CRITICAL(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        Log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }

private:
    static std::shared_ptr<spdlog::logger> logger;

    template<typename... Args>
    static void Log(spdlog::level::level_enum level, spdlog::format_string_t<Args...> fmt, Args&&... args) {
        if (logger) {
            logger->log(level, fmt, std::forward<Args>(args)...);
        }
    }
};