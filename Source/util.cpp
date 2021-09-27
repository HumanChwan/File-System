#include <iostream>

#include "../Header/util.h"

std::vector<std::string> FS::split( const std::string& str, char split_char) {
  // std::cout << str;
  std::vector<std::string> a;
  std::string temp = "";
  for (char x : str) {
    if (x == split_char) {
      a.push_back(temp);
      temp = "";
    } else {
      temp += x;
    }
  }

  a.push_back(temp);

  return a;
}
