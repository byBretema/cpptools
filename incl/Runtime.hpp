#pragma once

// ========================================================================= //
// ================= https://github.com/gpakosz/whereami =================== //
// ========================================================================= //


#ifndef WHEREAMI_H
#define WHEREAMI_H
#ifdef __cplusplus
extern "C" {
#endif
#ifndef WAI_FUNCSPEC
#define WAI_FUNCSPEC
#endif
#ifndef WAI_PREFIX
#define WAI_PREFIX(function) wai_##function
#endif
WAI_FUNCSPEC
int WAI_PREFIX(getExecutablePath)(char* out, int capacity, int* dirname_length);
WAI_FUNCSPEC
int WAI_PREFIX(getModulePath)(char* out, int capacity, int* dirname_length);
#ifdef __cplusplus
}
#endif
#endif // #ifndef WHEREAMI_H


// ========================================================================= //
// ============================= DAC - Runtime ============================= //
// ========================================================================= //

#include <string>

namespace dac {

class Runtime {
public:
  static std::string exePath();
};

} // namespace dac
