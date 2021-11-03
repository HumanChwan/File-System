#include "../Header/Command.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Header/File.h"
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
    } else if (base_command == "touch") {
        touch(split_commands);
    } else if (base_command == "cat") {
        cat(split_commands);
    } else if (base_command == "exit") {
        exit();
    } else {
        Out::Error(base_command + ": unrecognized command");
        return;
    }
}

void Command::change_directory(const std::vector<std::string>& args) {
    if (args.size() > 1) {
        Out::Error("Too many arguments");
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

    // System* present_state = state;

    std::string temp = "";
    // "helo"
    for (char x : args[0]) {
        if (x == '/') {
            state->move_to_dir(temp);
            temp = "";
        } else {
            temp += x;
        }
    }

    state->present->make_dir(temp);
    // state = present_state;
}

void Command::touch(const std::vector<std::string>& args) {
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
            state->move_to_dir(temp);
            temp = "";
        } else {
            temp += x;
        }
    }

    state->present->touch(temp);
}

void Command::list(const std::vector<std::string>& args) {
    std::map<std::string, bool> flags;

    for (std::string flag : args) {
        flags[flag] = true;
    }

    state->present->list(flags["-a"] || flags["--all"]);
}

void Command::cat(const std::vector<std::string>& args) {
    if (args.size() > 2) {
        Out::Error("Too many arguments");
    }

    bool stdin_cat = (args.size() == 0 || args[0] == ">");
    bool stdout_cat = (args.size() == 1 || args[1] == "<");

    std::string buffer;
    if (stdin_cat) {
        std::string line;
        while (true) {
            std::getline(std::cin, line);
            if (line[0] == '\x1b') {
                break;
            }
            buffer += line + "\n";
        }
    } else {
        // File to buffer
        if (state->present->find_file(args[0])) {
            File* file = state->present->get_file(args[0]);
            buffer = file->content();
        } else {
            Out::Error("File not found");
        }
    }

    if (stdout_cat) {
        Out::Log(buffer);
    } else {
        // buffer to file
        if (state->present->find_file(args[1])) {
            File* file = state->present->get_file(args[1]);
            *file = buffer;
        } else {
            Out::Error("File not found");
        }
    }
}

void Command::exit() { state->exit(); }