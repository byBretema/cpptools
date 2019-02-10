#pragma once

#include <string>

namespace dac {

class Files {
public:
  static bool ok(const std::string& path, bool log = false);
};

} // namespace dac
