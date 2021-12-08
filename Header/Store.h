#ifndef FSSTORE
#define FSSTORE

#include <string>

#include "Directory.h"

namespace FS {
constexpr const char* EXT = ".fs";
std::string getHashedPassword(const std::string& user);
Directory* Parser(const std::string& user);
void Save(const std::string& user, const std::string& hash,
          const Directory* root);
};  // namespace FS

#endif