#include "Files.hpp"

#include <fstream>
#include "Logger.hpp"

namespace dac {

bool Files::ok(const std::string& path, bool log) {
  bool ok = std::fstream(path).good();
  if (log && !ok) dInfo("Problems with file {}", path);
  return ok;
}

} // namespace dac
