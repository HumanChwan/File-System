#ifndef FSUTIL
#define FSUTIL

#include <string>
#include <vector>

namespace FS {
std::vector<std::string> split(const std::string& str, char split_char = ' ');
std::string join(const std::vector<std::string>& arr, char join_char = ' ');
std::string hashIt(const std::string& base);
};  // namespace FS

#endif
