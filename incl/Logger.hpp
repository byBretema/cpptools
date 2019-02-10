#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace dac {

typedef std::shared_ptr<spdlog::logger> _LogType;

class Logger {

#define PATTERN_PRINT "%v"
#define PATTERN_ALERT "[%T] (%t @ %@) => %^%v%$"

private:
  // Patterns
  static const char* m_patternPrints;
  static const char* m_patternAlerts;

  // Loggers
  static _LogType m_info;
  static _LogType m_error;
  static _LogType m_print;


public:
  // Getter of info logger
  static _LogType& info();
  // Getter of error logger
  static _LogType& error();
  // Getter of print logger
  static _LogType& print();
};

} // namespace dac


#define dInfo(...) SPDLOG_LOGGER_INFO(dac::Logger::info(), __VA_ARGS__);
#define dErr(...) SPDLOG_LOGGER_ERROR(dac::Logger::error(), __VA_ARGS__);
#define dPrint(...) SPDLOG_LOGGER_INFO(dac::Logger::print(), __VA_ARGS__);
