#include "Logger.hpp"

namespace DAC {

// For avoid to user explicit call of init method.
std::once_flag Logger::m_once_init;

// PATTERNS
const char *Logger::m_patternPrints = "%v";
const char *Logger::m_patternAlerts = "[%T] (%t @ %@) => %^%v%$";

// DEFINE SHARED PTRs
std::shared_ptr<spdlog::logger> Logger::m_info =
    spdlog::stdout_color_mt("INFO");
std::shared_ptr<spdlog::logger> Logger::m_error =
    spdlog::stderr_color_mt("ERROR");
std::shared_ptr<spdlog::logger> Logger::m_print =
    spdlog::stdout_color_mt("PRINT");

// "GETTERS"
std::shared_ptr<spdlog::logger> &Logger::info() {
  std::call_once(m_once_init, init);
  return m_info;
}
std::shared_ptr<spdlog::logger> &Logger::error() {
  std::call_once(m_once_init, init);
  return m_error;
}
std::shared_ptr<spdlog::logger> &Logger::print() {
  std::call_once(m_once_init, init);
  return m_print;
}

// INIT: Just setup patterns for loggers
void Logger::init() {
  m_info->set_pattern(m_patternAlerts);
  m_error->set_pattern(m_patternAlerts);
  m_print->set_pattern(m_patternPrints);
}

} // namespace DAC
