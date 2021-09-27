#ifndef FSOUT
#define FSOUT

#include <string>
#include <iostream>

class Out {
private:
public:
  Out();

  static void Error(const std::string& message);

  static void Base_Prompt(const std::string& path);

  static void Log(const std::string& message);
};

#endif
