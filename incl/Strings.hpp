#pragma once

#include <string>
#include <vector>

namespace DAC { namespace Strings {

  /// Get as std::string the content of a given file
  std::string fromFile(const std::string& filePath);

  /// split gives a vector with splitted strings
  std::vector<std::string> split(const std::string& str,
                                 const std::string& delimeter);

}} // namespace DAC::Strings
