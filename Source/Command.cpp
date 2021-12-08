#include "../Header/Command.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../Header/Directory.h"
#include "../Header/File.h"
#include "../Header/Node.h"
#include "../Header/Out.h"
#include "../Header/Store.h"
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

    if (base_command == "login")
        login();
    else if (base_command == "logout")
        logout();
    else if (base_command == "cd")
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
    else if (base_command == "rm")
        remove(split_commands);
    else if (base_command == "tree")
        tree(split_commands);
    else if (base_command == "clear")
        clear();
    else if (base_command == "exit")
        exit();
    else
        Out::Error(base_command + ": unrecognized command");
}

void Command::login() {
    if (state->is_logged_in()) {
        Out::Error("User [\"" + state->get_user() +
                   "\"] is already logged in.");
        return;
    }
    Out::Interactive("Username:");
    std::string username;
    getline(std::cin, username);

    try {
        std::string hashPassword = FS::getHashedPassword(username);

        Out::Interactive("Password:");
        std::string password;
        getline(std::cin, password);

        if (FS::hashIt(password) != hashPassword) {
            Out::Error("Password do not match");
            return;
        } else {
            Out::Log("Welcome back \"" + username + "\"");
            state->set_hashed_password(hashPassword);
            state->set_user(username);
            state->toggle_login_status();
            // state->reset(FS::Parser(username));
            // Parse the shit out of the file...()
        }
    } catch (const char*& error) {
        Out::Error("No user [\"" + username + "\"], found");
        Out::Interactive("Would you like to create a new user with username: " +
                         username + "? (y/n)");
        char choice = getchar();
        std::cin.ignore();
        if (choice != 'Y' && choice != 'y') {
            return;
        }
        Out::Log("Created new user with username: " + username);

        std::string password;
        Out::Interactive("Create Password:");
        getline(std::cin, password);

        password = FS::hashIt(password);
        Out::Log("Welcome \"" + username + "\"");
        state->set_hashed_password(password);
        state->set_user(username);
        state->toggle_login_status();

        // FS::Save(username, password, state->root());
    }
}

void Command::logout() {
    if (!state->is_logged_in()) {
        Out::Error("No User is logged in");
        return;
    }
    FS::Save(state->get_user(), state->get_hashed_password(), state->root());
    state->toggle_login_status();
    state->reset(nullptr);
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
    if (args.size() < 1) {
        Out::Error("Missing necessary arguments.");
        return;
    }

    for (const std::string& new_dir : args) {
        std::vector<std::string> new_directory_path = FS::split(new_dir, '/');
        std::string new_directory_name = new_directory_path.back();
        new_directory_path.pop_back();

        Directory* parent = crawl(state->present, new_directory_path);
        if (parent == nullptr) {
            return;
        }

        parent->make_dir(new_directory_name);
    }
}

void Command::touch(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        Out::Error("Missing necessary arguments.");
        return;
    }

    for (const std::string& arg : args) {
        std::vector<std::string> new_file_path = FS::split(arg, '/');
        std::string new_file_name = new_file_path.back();
        new_file_path.pop_back();

        Directory* parent = crawl(state->present, new_file_path);
        if (parent == nullptr) {
            return;
        }

        parent->touch(new_file_name);
    }
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
    // 0: in, 1: out
    std::vector<std::string> nodes[2];
    bool out = false;
    bool in = true;
    // format considered: cat < [....in....] > [....out....]
    /*
        for command: "cat > [....out....]"
        it is read as: cat < 1 > [....out....]

        for command: "cat < [....in....]" or "cat [....in....]"
        it is read as: cat < [....in....] > 2
    */
    for (const std::string& arg : args) {
        if (arg == ">") {
            if (out) {
                Out::Error("Invalid arguments!");
                return;
            }
            out = true;
            in = false;
            continue;
        } else if (arg == "<") {
            if (!in) {
                Out::Error("Invalid arguments!");
                return;
            }
            continue;
        }

        nodes[out].push_back(arg);
    }

    bool stdin_cat = (nodes[0].size() == 0);
    bool stdout_cat = (nodes[1].size() == 0);

    std::string buffer;
    if (stdin_cat) {
        std::string line;
        while (true) {
            std::getline(std::cin, line);
            if (line[0] == '\x1b') break;
            buffer += line + '\n';
        }
    } else {
        // File to buffer
        for (const std::string& buffer_files : nodes[0]) {
            std::vector<std::string> file_path = FS::split(buffer_files, '/');
            std::string file_name = file_path.back();
            file_path.pop_back();

            Directory* parent = crawl(state->present, file_path);
            if (parent == nullptr) {
                return;
            }

            File* file = parent->get_file(file_name);
            if (file == nullptr) {
                Out::Error(file_name + ": File not found");
                continue;
            }

            buffer += file->content();
        }
    }

    if (stdout_cat) {
        Out::Log(buffer);
    } else {
        // buffer to file
        for (const std::string& buffer_files : nodes[1]) {
            std::vector<std::string> file_path = FS::split(buffer_files, '/');
            std::string file_name = file_path.back();
            file_path.pop_back();

            Directory* parent = crawl(state->present, file_path);
            if (parent == nullptr) {
                return;
            }

            File* file = parent->get_file(file_name);
            if (file == nullptr) {
                Out::Error(file_name + ": File not found");
                continue;
            }

            file->overwrite_content(buffer);
        }
    }
}

void Command::move(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        Out::Error("Missing necessary arguments");
        return;
    }

    Directory* destination_directory = crawl(state->present, args.back());
    if (destination_directory == nullptr) {
        Out::Error("Destination directory does not exist");
        return;
    }

    std::vector<std::string> nodes = args;
    nodes.pop_back();
    for (std::string& input_node : nodes) {
        std::vector<std::string> source_path = FS::split(input_node, '/');
        std::string node_name = source_path.back();
        source_path.pop_back();
        Directory* source_parent_directory = crawl(state->present, source_path);
        if (source_parent_directory == nullptr) {
            Out::Error("Source path does not exist");
            return;
        }

        Node* node = source_parent_directory->get_node(node_name);
        if (node == nullptr) {
            Out::Error("Source path does not exist");
            return;
        }

        if (destination_directory->has_ancestor(node)) {
            Out::Error("Cannot move source to its subdirectory");
            continue;
        }

        if (destination_directory->find_node(node_name)) {
            Out::Error(node_name + ": exists in destination directory");
            continue;
        }

        source_parent_directory->remove_node(node);
        destination_directory->push_node(node);
    }
}

void Command::tree(const std::vector<std::string>& args) {
    if (args.size() > 1) {
        Out::Error("Too many arguments");
        return;
    }

    Directory* selected_root = state->present;
    if (args.size() == 1) {
        selected_root = crawl(state->present, args[0]);
        if (selected_root == nullptr) {
            return;
        }
    }

    Out::Log(Terminal::PURPLE +
             (selected_root == state->present ? "." : args[0]));
    Out::Default();
    selected_root->get_node(".")->traverse();
    Out::Log(Terminal::DEFAULT);
}

void Command::remove(const std::vector<std::string>& args) {
    std::map<std::string, bool> flag;
    flag["-r"] = false;
    flag["-d"] = false;
    std::vector<std::string> paths;
    for (const std::string& x : args) {
        if (x[0] == '-') {
            if (!flag.count(x)) {
                Out::Error(x + " flag doesn't exist");
                return;
            } else {
                flag[x] = true;
            }
        } else {
            paths.push_back(x);
        }
    }

    for (const std::string& path : paths) {
        std::vector<std::string> node_path = FS::split(path, '/');
        std::string node_name = node_path.back();
        node_path.pop_back();
        Directory* parent_directory = crawl(state->present, node_path);
        if (parent_directory == nullptr) {
            Out::Error(path + ": Path does not exist");
            continue;
        }

        Node* node = parent_directory->get_node(node_name);
        if (node == nullptr) {
            Out::Error(path + ": Path does not exist");
            return;
        }

        if (node->get_type() == NodeType::FILE_NODE) {
            parent_directory->remove_node(node);
            delete node;
            return;
        }

        if (!flag["-d"]) {
            Out::Error(node->get_name() + " is a directory");
            return;
        }

        if (!node->get_data().directory->empty() && !flag["-r"]) {
            Out::Error(node->get_name() + " is not an empty directory");
            return;
        }

        parent_directory->remove_node(node);
        delete node;
    }
}

void Command::clear() { Out::Clear(); }

void Command::exit() { state->exit(); }