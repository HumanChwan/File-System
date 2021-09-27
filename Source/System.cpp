#include "../Header/System.h"
#include "../Header/Command.h"

System::System() {
  root = new Directory(nullptr, "root");
  present = root;
  live = true;
}

void System::init() {
  Out();

  while(live) {
    Out::Base_Prompt(present->path());
    std::string command;
    getline(std::cin, command);
    Command new_command(this, command);
  }
}

void System::move_to_dir(const std::string& dirname) {
    present = present->get_dir(dirname);
}

System::~System() {
  delete root;
}
