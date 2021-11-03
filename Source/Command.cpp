#include "../Header/Command.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Header/Out.h"
#include "../Header/System.h"
#include "../Header/util.h"

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
        list(split_commands);
    } else if (base_command == "exit") {
        exit();
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
        state->move_to_root();
        return;
    }

    std::vector<std::string> split_dir = FS::split(args[0], '/');

    for (std::string x : split_dir) {
        if (state->present->find_sub_directory(x)) {
            state->move_to_dir(x);
        } else {
            Out::Error("Invalid Path");
            return;
        }
    }
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

    System* present_state = state;

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
    state = present_state;
}

void Command::list(const std::vector<std::string>& args) {
    std::map<std::string, bool> flags;
    for (std::string flag : args) {
        flags[flag] = true;
    }

    state->present->list(flags["-a"] || flags["--all"]);
}

void Command::exit() { state->exit(); }