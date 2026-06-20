#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

enum class LogLevel { NOTE, INFO, WARN, ERROR };

class Logger {
public:
  // Initialize console for colors (mainly required for Windows)
  static void init() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
      DWORD dwMode = 0;
      if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
      }
    }
#endif
  }

  template <typename... Args> static void log(LogLevel level, Args &&...args) {
    // Print timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto local_time = *std::localtime(&time_t_now);

    std::cout << "[" << std::put_time(&local_time, "%H:%M:%S") << "] ";

    // Print level tag with color
    switch (level) {
    case LogLevel::NOTE:
      std::cout << "\033[36m[NOTE]\033[0m "; // Cyan
      break;
    case LogLevel::INFO:
      std::cout << "\033[32m[INFO]\033[0m "; // Green
      break;
    case LogLevel::WARN:
      std::cout << "\033[33m[WARN]\033[0m "; // Yellow
      break;
    case LogLevel::ERROR:
      std::cout << "\033[31m[ERROR]\033[0m "; // Red
      break;
    }

    // Print the actual message using fold expressions (C++17)
    (std::cout << ... << args) << std::endl;
  }
};
