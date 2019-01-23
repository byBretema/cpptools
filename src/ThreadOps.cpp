#include "ThreadOps.hpp"
#include "Logger.hpp"

namespace DAC {

// Runs a function fn each wait time until flag is false;
void async_RunFuncEachTime(float sleepTime, bool *threadLiveFlag,
                           const std::function<void(void)> &func) {

  auto tFunc = [](float sleepTime, bool *threadLiveFlag,
                  const std::function<void(void)> &func) {
    try {

      while (*threadLiveFlag) {
        func();

        std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
      }

    } catch (std::exception &) {
      DacLog_INFO("THREAD DIE!");
    }
  };

  std::thread(tFunc, sleepTime, threadLiveFlag, func).detach();
}

} // namespace DAC
