#pragma once

#include <functional>

namespace dac {

class Async {
  using asyncFn = std::function<void(void)>;
  static void _periodic(float sleepTime, bool* threadFlag, const asyncFn& func);

public:
  // Runs a function fn each wait time until flag is false;
  static void periodic(float sleepTime, bool* threadFlag, const asyncFn& func);
};

} // namespace dac
