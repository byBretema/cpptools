#include "../incl/Logger.hpp"

#include <mutex>

namespace dac {

// ====================================================================== //
// ====================================================================== //
// Define loggers
// ====================================================================== //

_LogType Logger::m_info  = spdlog::stdout_color_mt("INFO");
_LogType Logger::m_error = spdlog::stderr_color_mt("ERROR");
_LogType Logger::m_print = spdlog::stdout_color_mt("PRINT");

// ====================================================================== //
// ====================================================================== //
// Getter of info logger
// ====================================================================== //

_LogType& Logger::info() {
  static std::once_flag infoOnceFlag;
  std::call_once(infoOnceFlag, [&]() { m_info->set_pattern(PATTERN_ALERT); });
  return m_info;
}

// ====================================================================== //
// ====================================================================== //
// Getter of error logger
// ====================================================================== //

_LogType& Logger::error() {
  static std::once_flag errorOnceFlag;
  std::call_once(errorOnceFlag, [&]() { m_error->set_pattern(PATTERN_ALERT); });
  return m_error;
}

// ====================================================================== //
// ====================================================================== //
// Getter of print logger
// ====================================================================== //

_LogType& Logger::print() {
  static std::once_flag printOnceFlag;
  std::call_once(printOnceFlag, [&]() { m_print->set_pattern(PATTERN_PRINT); });
  return m_print;
}

} // namespace dac
