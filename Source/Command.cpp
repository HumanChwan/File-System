#include <iostream>
#include <string>
#include <vector>

#include "../Header/Command.h"
#include "../Header/util.h"
#include "../Header/Out.h"
#include "../Header/System.h"


Command::Command(System* sys_state, const std::string& command) {
  std::vector<std::string> split_commands = FS::split(command);

  if (split_commands.size() == 0) {
    return;
  }

  std::string base_command = split_commands[0];

  split_commands.erase(split_commands.begin());

  state = sys_state;

  if (base_command == "cd") {
    change_directory(split_commands);
  } else if (base_command == "mkdir") {
    make_directory(split_commands);
  } else if (base_command == "ls") {
    if (split_commands.size()) {
      Out::Error("Too many arguments");
      return;
    }
    list();
  } else {
    Out::Error(base_command + ": unrecognized command");
    return;
  }
}

void Command::change_directory(const std::vector<std::string>& args) {
  if (args.size() > 1) {
    Out::Error("Too many arguments.");
    return;
  }

  if (args.size() < 1) {
    Out::Error("Missing necessary arguments.");
    return;
  }

  std::string temp = "";

  for (char x : args[0]) {
    if (x == '/') {
      if (temp == ".") {
        continue;
      } else if (temp == "..") {
        state->present = state->present->parent();
        continue;
      }

      if (!(state->present->find_sub_directory(temp))) {
        Out::Error("Invalid Path");
        return;
      }

      state->move_to_dir(temp);

      temp = "";
    } else {
      temp += x;
    }
  }

  if (temp == ".") {
    return;
  } else if (temp == "..") {
    state->present = state->present->parent();
    return;
  }

  if (!(state->present->find_sub_directory(temp))) {
    Out::Error("Invalid Path");
    return;
  }

  state->move_to_dir(temp);
}

void Command::make_directory(const std::vector<std::string>& args) {
  if (args.size() > 1) {
    Out::Error("Too many arguments.");
    return;
  }

  if (args.size() < 1) {
    Out::Error("Missing necessary arguments.");
    return;
  }

  std::string temp = "";
  for (char x : args[0]) {
    if (x == '/') {
      state->present->make_dir(temp);
      temp = "";
    } else {
      temp += x;
    }
  }

  state->present->make_dir(temp);
}

void Command::list() {
  state->present->list();
}
