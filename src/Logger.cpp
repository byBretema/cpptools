#include "Logger.hpp"

namespace dac {

// ====================================================================== //
// ====================================================================== //
// For avoid to user explicit call of init method.
// ====================================================================== //

std::once_flag Logger::m_once_init;


// ====================================================================== //
// ====================================================================== //
// Define patterns
// ====================================================================== //

const char* Logger::m_patternPrints = "%v";
const char* Logger::m_patternAlerts = "[%T] (%t @ %@) => %^%v%$";


// ====================================================================== //
// ====================================================================== //
// Define loggers
// ====================================================================== //

std::shared_ptr<spdlog::logger> Logger::m_info =
    spdlog::stdout_color_mt("INFO");
std::shared_ptr<spdlog::logger> Logger::m_error =
    spdlog::stderr_color_mt("ERROR");
std::shared_ptr<spdlog::logger> Logger::m_print =
    spdlog::stdout_color_mt("PRINT");


// ====================================================================== //
// ====================================================================== //
// Initialization: Just setup the patterns
// Its auto invoked from public methods
// ====================================================================== //

void Logger::init() {
  m_info->set_pattern(m_patternAlerts);
  m_error->set_pattern(m_patternAlerts);
  m_print->set_pattern(m_patternPrints);
}



// * ---  PUBLIC METHODS --- * //

// ====================================================================== //
// ====================================================================== //
// Detailed print mehtod, w/ thread, line and file data
// (NOTE: Output goes to stdout)
// ====================================================================== //

template <typename... Args>
void info(const Args&... args) {
  std::call_once(m_once_init, init);
  SPDLOG_LOGGER_INFO(m_info, args...);
}

// ====================================================================== //
// ====================================================================== //
// Error alert method, w/ thread, line and file data
// (NOTE: Output goes to stderr)
// ====================================================================== //

template <typename... Args>
void err(const Args&... args) {
  std::call_once(m_once_init, init);
  SPDLOG_LOGGER_ERROR(m_error, args...);
}

// ====================================================================== //
// ====================================================================== //
// Print mehtod (NOTE: Output goes to stdout)
// ====================================================================== //

template <typename... Args>
void print(const Args&... args) {
  std::call_once(m_once_init, init);
  SPDLOG_LOGGER_INFO(m_print, args...);
}



} // namespace dac
