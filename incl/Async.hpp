#pragma once

#include <functional>

namespace dac {

class Async {
  using asyncFn = std::function<void(void)>;
  using floatFn = std::function<float(void)>;

  static void _periodic(const floatFn& timeFn, bool* threadFlag,
                        const asyncFn& func);

public:
  // Runs a function fn each wait time until flag is false;
  static void periodic(const floatFn& timeFn, bool* threadFlag,
                       const asyncFn& func);
};

} // namespace dac
