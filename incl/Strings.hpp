#pragma once

#include <string>
#include <vector>

namespace dac {

class Strings {
public:
  /// Get as std::string the content of a given file
  static std::string fromFile(const std::string& filePath);

  /// Split gives a vector with splitted strings
  static std::vector<std::string> split(const std::string& str,
                                        const std::string& delimeter);
};

} // namespace dac
