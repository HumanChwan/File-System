#include "../Header/System.h"

#include "../Header/Command.h"
#include "../Header/Out.h"

System::System() {
    root = new Directory(nullptr, "root");
    present = root;
    live = true;
    user = "user";
}

void System::init() {
    Out();

    while (live) {
        Out::Base_Prompt(get_user(), present->path());
        std::string command;
        getline(std::cin, command);
        Command new_command(this, command);
    }
}

std::string System::get_user() { return user; }

bool System::move_to_dir(const std::string& dirname) {
    Directory* sub = present->get_dir(dirname);
    if (sub == nullptr) return false;

    present = sub;
    return true;
}

bool System::move_to_dir(Directory* directory) {
    if (directory == nullptr) return false;

    present = directory;
    return true;
}

void System::move_to_root() { present = root; }

void System::exit() {
    Out::Log("Exiting...");
    live = false;
    Out::Log("Exited!");
}

System::~System() { delete root; }
