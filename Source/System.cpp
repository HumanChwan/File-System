#include "../Header/System.h"

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

System::~System() {
  delete root;
}
