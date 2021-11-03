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

void System::move_to_dir(const std::string& dirname) {
    present = present->get_dir(dirname);
}

void System::move_to_dir(Directory& directory) { present = &directory; }

void System::move_to_root() { present = root; }

void System::exit() {
    Out::Log("Exiting...");
    live = false;
    Out::Log("Exited!");
}

System::~System() { delete root; }
