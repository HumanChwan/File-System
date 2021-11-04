#ifndef FSOUT
#define FSOUT

#include <iostream>
#include <string>

class System;

namespace Terminal {
constexpr const char* RED = "\x1b[31m";
constexpr const char* GREEN = "\x1b[32m";
constexpr const char* YELLOW = "\x1b[33m";
constexpr const char* BLUE = "\x1b[34m";
constexpr const char* PURPLE = "\x1b[35m";
constexpr const char* CYAN = "\x1b[36m";
constexpr const char* DEFAULT = "\x1b[0m";
};  // namespace Terminal
class Out {
   private:
   public:
    Out();

    static void Error(const std::string& message);

    static void Base_Prompt(const std::string& state, const std::string& path);

    static void Log(const std::string& message);

    static void Clear();
};

#endif
