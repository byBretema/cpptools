#pragma once

#include <functional>

namespace DAC {

// Runs a function fn each wait time until flag is false;
void async_RunFuncEachTime(float sleepTime, bool *threadLiveFlag,
                           const std::function<void(void)> &func);

} // namespace DAC
