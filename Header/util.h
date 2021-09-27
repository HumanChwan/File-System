#ifndef FSUTIL
#define FSUTIL

#include <vector>
#include <string>

namespace FS {
  std::vector<std::string> split(const std::string& str, char split_char = ' ');
};

#endif
