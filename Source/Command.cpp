#include "../Header/Command.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Header/Directory.h"
#include "../Header/File.h"
#include "../Header/Node.h"
#include "../Header/Out.h"
#include "../Header/System.h"
#include "../Header/util.h"

Directory* Command::crawl(Directory* start,
                          const std::vector<std::string>& path) {
    Directory* crawler = start;
    for (std::string sub_path : path) {
        Directory* sub = crawler->get_dir(sub_path);
        if (sub == nullptr) {
            Out::Error("Directory not found");
            return nullptr;
        }
        crawler = sub;
    }

    return crawler;
}

Directory* Command::crawl(Directory* start, const std::string& path) {
    return crawl(start, FS::split(path, '/'));
}

Command::Command(System* sys_state, const std::string& command) {
    std::vector<std::string> split_commands = FS::split(command);

    if (split_commands.size() == 0) {
        return;
    }

    std::string base_command = split_commands[0];

    split_commands.erase(split_commands.begin());

    state = sys_state;

    if (base_command == "cd")
        change_directory(split_commands);
    else if (base_command == "mkdir")
        make_directory(split_commands);
    else if (base_command == "ls")
        list(split_commands);
    else if (base_command == "touch")
        touch(split_commands);
    else if (base_command == "cat")
        cat(split_commands);
    else if (base_command == "mv")
        move(split_commands);
    else if (base_command == "clear")
        clear();
    else if (base_command == "exit")
        exit();
    else
        Out::Error(base_command + ": unrecognized command");
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
    state->move_to_dir(crawl(state->present, split_dir));
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

    std::vector<std::string> new_directory_path = FS::split(args[0], '/');
    std::string new_directory_name = new_directory_path.back();
    new_directory_path.pop_back();

    Directory* parent = crawl(state->present, new_directory_path);
    if (parent == nullptr) {
        return;
    }

    parent->make_dir(new_directory_name);
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

    std::vector<std::string> new_file_path = FS::split(args[0], '/');
    std::string new_file_name = new_file_path.back();
    new_file_path.pop_back();

    Directory* parent = crawl(state->present, new_file_path);
    if (parent == nullptr) {
        return;
    }

    parent->touch(new_file_name);
}

void Command::list(const std::vector<std::string>& args) {
    std::map<std::string, bool> flags;
    std::string path = "";

    for (std::string flag : args) {
        if (flag[0] == '-') {
            flags[flag] = true;
        } else {
            path = flag;
        }
    }

    Directory* directory = crawl(state->present, path);
    if (directory == nullptr) {
        return;
    }

    directory->list(flags["-a"] || flags["--all"]);
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
        std::vector<std::string> file_path = FS::split(args[0], '/');
        std::string file_name = file_path.back();
        file_path.pop_back();

        Directory* parent = crawl(state->present, file_path);
        if (parent == nullptr) {
            return;
        }

        File* file = parent->get_file(file_name);
        if (file == nullptr) {
            Out::Error("File not found");
            return;
        }

        buffer = file->content();
    }

    if (stdout_cat) {
        Out::Log(buffer);
    } else {
        // buffer to file
        std::vector<std::string> file_path = FS::split(args[1], '/');
        std::string file_name = file_path.back();
        file_path.pop_back();

        Directory* parent = crawl(state->present, file_path);
        if (parent == nullptr) {
            return;
        }

        File* file = parent->get_file(file_name);
        if (file == nullptr) {
            Out::Error("File not found");
            return;
        }

        file->overwrite_content(buffer);
    }
}

void Command::move(const std::vector<std::string>& args) {
    if (args.size() > 2) {
        Out::Error("Too many arguments");
        return;
    }

    if (args.size() < 2) {
        Out::Error("Missing necessary arguments");
        return;
    }

    std::vector<std::string> source_path = FS::split(args[0], '/');
    std::string node_name = source_path.back();
    source_path.pop_back();
    Directory* source_parent_directory = crawl(state->present, source_path);
    if (source_parent_directory == nullptr) {
        return;
    }

    Node* node = source_parent_directory->get_node(node_name);
    if (node == nullptr) {
        return;
    }

    Directory* destination_directory = crawl(state->present, args[1]);
    if (destination_directory == nullptr) {
        Out::Error("Destination directory does not exist");
        return;
    }

    if (destination_directory->find_node(node_name)) {
        Out::Error(node_name + ": exists in destination directory");
    }

    source_parent_directory->remove_node(node);
    destination_directory->push_node(node);
}

void Command::clear() { Out::Clear(); }

void Command::exit() { state->exit(); }