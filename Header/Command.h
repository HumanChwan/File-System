#ifndef COMMAND
#define COMMAND

#include <string>
#include <vector>

class System;

class Command {
private:
  System* state;
public:
  Command(System* sys_state, const std::string& command);

  void change_directory(const std::vector<std::string>& args);

  void make_directory(const std::vector<std::string>& args);

  void list();
};

#endif
