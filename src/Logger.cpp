#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::Init() {
    try {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

        logger = std::make_shared<spdlog::logger>("console", consoleSink);
        logger->set_level(spdlog::level::trace);

        spdlog::register_logger(logger);

        INFO("Logger initialized successfully");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}

void Logger::Shutdown() {
    if (logger) {
        INFO("Logger shutting down...");
        spdlog::shutdown();
    }
}

void Logger::AttachConsole() {
    AllocConsole();
    FILE* dummy;
    freopen_s(&dummy, "CONOUT$", "w", stdout);
    freopen_s(&dummy, "CONOUT$", "w", stderr);
    freopen_s(&dummy, "CONIN$", "r", stdin);
    SetConsoleTitle(L"Logs");
}

void Logger::DetachConsole() {
    FreeConsole();
}

void Logger::HideConsole() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void Logger::ShowConsole() {
    ShowWindow(GetConsoleWindow(), SW_SHOW);
}

bool Logger::IsConsoleVisible() {
    return IsWindowVisible(GetConsoleWindow()) != 0;
}

void Logger::ToggleConsole() {
    if (IsConsoleVisible()) {
        HideConsole();
    } else {
        ShowConsole();
    }
}