#pragma once

#include <mutex>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace DAC {

class Logger {

private:
  // For avoid to user explicit call of init method.
  static std::once_flag m_once_init;

  // PATTERNS
  static const char* m_patternPrints;
  static const char* m_patternAlerts;

  // DECLARE SHARED PTRs
  static std::shared_ptr<spdlog::logger> m_info;
  static std::shared_ptr<spdlog::logger> m_error;
  static std::shared_ptr<spdlog::logger> m_print;

public:
  // "GETTERS"
  static std::shared_ptr<spdlog::logger>& info();
  static std::shared_ptr<spdlog::logger>& error();
  static std::shared_ptr<spdlog::logger>& print();

  // INIT: Just setup patterns for loggers
  static void init();
};

} // namespace DAC

// Comfortable macros
#define DacLog_INFO(...) SPDLOG_LOGGER_INFO(DAC::Logger::info(), __VA_ARGS__)
#define DacLog_ERR(...) SPDLOG_LOGGER_ERROR(DAC::Logger::error(), __VA_ARGS__)
#define DacLog_WARN(...) SPDLOG_LOGGER_WARN(DAC::Logger::error(), __VA_ARGS__)
#define DacLog_PRINT(...) SPDLOG_LOGGER_INFO(DAC::Logger::print(), __VA_ARGS__)
