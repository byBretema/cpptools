#include "Async.hpp"
#include "Logger.hpp"

namespace dac {

// ====================================================================== //
// ====================================================================== //
// Runs a function fn each wait time until flag is false;
// ====================================================================== //

void Async::periodic(float sleepTime, bool* threadFlag, const asyncFn& func) {

  // * --- Lambada func to run on detached thread --- * //

  auto tFunc = [](float sleepTime, bool* threadFlag, const asyncFn& func) {
    try {
      while (*threadFlag) {
        func();
        std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
      }
    } catch (std::exception&) { dlog::info("THREAD DIE!"); }
  };

  // * --- Launch thread --- * //

  std::thread(tFunc, sleepTime, threadFlag, func).detach();
}

} // namespace dac
