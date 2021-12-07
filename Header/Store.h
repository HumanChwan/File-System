#ifndef FSSTORE
#define FSSTORE

#include <string>

namespace FS {
std::string getHashedPassword(const std::string& user);
void Parser();
void Save(const std::string& user, const std::string& hash);
};  // namespace FS

#endif