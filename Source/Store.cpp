#include "../Header/Store.h"

#include <fstream>

#include "../Header/util.h"

std::string FS::getHashedPassword(const std::string& user) {
    std::ifstream f_in("Data/" + user + FS::EXT);
    if (f_in.fail()) {
        throw("User does not exist.");
    }

    std::string hashedPassword;
    getline(f_in, hashedPassword);
    f_in.close();

    return hashedPassword;
}

void data_to_file(std::ofstream& f_out, const Directory* subroot, int tabs) {
    std::string pre_tabs = "";
    for (int i = 0; i < tabs; ++i) pre_tabs += "\t";
    f_out << pre_tabs << subroot->get_dirname() << FS::NTS << "D\n";
    for (Node* node : *subroot) {
        if (node->parent() || node->self()) {
            continue;
        }
        if (node->get_type() == NodeType::FILE_NODE) {
            f_out << pre_tabs << "\t" << node->get_data().file->get_filename()
                  << FS::NTS << "F\n";
            f_out << node->get_data().file->content() << FS::EON << '\n';
        } else {
            data_to_file(f_out, node->get_data().directory, tabs + 1);
        }
    }
    f_out << FS::EON << '\n';
}

Node* file_to_data(std::ifstream& f_in, Directory* parent, int tabs) {
    std::string buffer;
    getline(f_in, buffer);
    if (buffer[0] == FS::EON) {
        return nullptr;
    }
    buffer = buffer.substr(tabs);
    std::vector<std::string> node_description = FS::split(buffer, FS::NTS);
    buffer = node_description.front();

    if (node_description.back() == "F") {
        File* file = new File(buffer, parent);
        for (getline(f_in, buffer); buffer[0] != FS::EON;
             getline(f_in, buffer)) {
            file->append_content(buffer + '\n');
        }
        return new Node(file);
    }

    Directory* sub_tree_root = new Directory(parent, buffer);
    while (true) {
        Node* child = file_to_data(f_in, sub_tree_root, tabs + 1);
        if (child == nullptr) break;
        sub_tree_root->push_node(child);
    }

    return new Node(sub_tree_root);
}

Directory* FS::Parser(const std::string& user) {
    std::ifstream f_in("Data/" + user + FS::EXT, std::ios::in);
    std::string buffer;

    // reading the hashedPassword
    getline(f_in, buffer);

    Directory* root = file_to_data(f_in, nullptr, 0)->get_data().directory;
    f_in.close();
    return root;
}

void FS::Save(const std::string& user, const std::string& hash,
              const Directory* root) {
    std::ofstream f_out("Data/" + user + FS::EXT, std::ios::out);
    f_out << hash << "\n";
    data_to_file(f_out, root, 0);
    f_out.close();
}