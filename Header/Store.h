#ifndef FSSTORE
#define FSSTORE

#include <string>

#include "Directory.h"

namespace FS {
constexpr const char* EXT = ".fs";
// End of Node
constexpr char EON = '\x1b';
// Node Type Separator
constexpr char NTS = '\x11';
std::string getHashedPassword(const std::string& user);
Directory* Parser(const std::string& user);
void Save(const std::string& user, const std::string& hash,
          const Directory* root);
};  // namespace FS

#endif