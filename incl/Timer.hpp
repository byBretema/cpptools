#pragma once
#include <chrono>
#include <string>


namespace dac {

// Eye candy types
using StdClock  = std::chrono::steady_clock;
using Seconds   = std::chrono::duration<double>;
using TimePoint = std::chrono::time_point<StdClock, Seconds>;

// Count time until its destruction and print a messagge
class Timer {
private:
  std::string m_promptMsg;
  TimePoint   m_initTimeStamp;

  // Get a chrono time point
  TimePoint now() const;

  // Compute elapsed time
  double elapsedTime() const;

public:
  // Constructor
  Timer(const std::string& msg = "");

  // Destructor
  ~Timer();
};

} // namespace dac
