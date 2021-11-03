#ifndef FSUTIL
#define FSUTIL

#include <string>
#include <vector>

namespace FS {
std::vector<std::string> split(const std::string& str, char split_char = ' ');
};

#endif
