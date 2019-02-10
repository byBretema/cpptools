#include "../incl/Async.hpp"
#include "../incl/Logger.hpp"

namespace dac {


// ====================================================================== //
// ====================================================================== //
// Runs a function fn each wait time until flag is false;
// ====================================================================== //

void Async::_periodic(float sleepTime, bool* threadFlag, const asyncFn& func) {
  try {
    while (*threadFlag) {
      func();
      std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
    }
  } catch (std::exception&) { dInfo("THREAD DIE!"); }
}

// ====================================================================== //
// ====================================================================== //
// Periodic function wrapper that runs it in a separated thead
// ====================================================================== //

void Async::periodic(float sleepTime, bool* threadFlag, const asyncFn& func) {
  std::thread(_periodic, sleepTime, threadFlag, func).detach();
}

} // namespace dac
