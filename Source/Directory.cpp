#include "../Header/Directory.h"

// <------Constructor-------->
Directory::Directory(Directory* parentDir, const std::string& dirname) {
    m_Parent = parentDir;
    m_Dirname = dirname;

    m_Path = "";
    if (parentDir != nullptr) {
        m_Nodes.push_back(new Node(parentDir, true));
        m_Nodes.push_back(new Node(this, false, true));

        m_Path = parentDir->path() + dirname;
    } else {
        m_Nodes.push_back(new Node(this, false, true));
        m_Parent = this;
    }

    m_Path += "/";
}

// <------Public Methods-------->
bool Directory::find_file(const std::string& filename) const {
    for (Node* node : m_Nodes) {
        switch (node->get_type()) {
            case NodeType::FILE_NODE:
                if (node->get_name() == filename) {
                    return true;
                }
                break;
            case NodeType::DIRECTORY_NODE:
                if (node->get_name() == filename) {
                    Out::Error(filename + ": is a directory");
                    return false;
                }
                break;
            default:
                Out::Error("FATAL ERROR");
                return false;
        }
    }

    return false;
}

File* Directory::get_file(const std::string& filename) const {
    for (Node* node : m_Nodes) {
        if (node->get_name() == filename) {
            if (node->get_type() == NodeType::FILE_NODE) {
                return node->get_data().file;
            }
        }
    }

    return nullptr;
}

bool Directory::find_sub_directory(const std::string& dirname) const {
    for (Node* node : m_Nodes) {
        if (node->get_name() == dirname) {
            if (node->get_type() == NodeType::DIRECTORY_NODE) {
                return true;
            }

            Out::Error(dirname + ": is a file!");
            return false;
        }
    }

    return false;
}

Directory* Directory::get_dir(const std::string& dirname) {
    for (Node* node : m_Nodes) {
        if (node->get_name() == dirname) {
            if (node->get_type() == NodeType::DIRECTORY_NODE) {
                return node->get_data().directory;
            }
        }
    }

    return nullptr;
}

bool Directory::find_node(const std::string& node_name) {
    for (Node* node : m_Nodes) {
        if (node->get_name() == node_name) {
            return true;
        }
    }

    return false;
}

Node* Directory::get_node(const std::string& node_name) {
    for (Node* node : m_Nodes) {
        if (node->get_name() == node_name) {
            return node;
        }
    }

    return nullptr;
}

void Directory::push_node(Node* node) {
    if (node->get_type() == NodeType::FILE_NODE)
        node->get_data().file->set_parent_directory(this);
    else {
        Directory* directory = node->get_data().directory;
        directory->set_parent_directory(this);
        directory->set_path(m_Path + directory->get_dirname());
    }
    m_Nodes.push_back(node);
}

void Directory::remove_node(Node* node) { m_Nodes.remove(node); }

Directory* Directory::parent() { return m_Parent; }
void Directory::set_parent_directory(Directory* directory) {
    m_Parent = directory;
}

void Directory::make_dir(const std::string& dirname) {
    if (find_sub_directory(dirname)) {
        Out::Error("directory with same path already exists");
        return;
    }

    Directory* new_dir = new Directory(this, dirname);
    m_Nodes.push_back(new Node(new_dir));
}

void Directory::touch(const std::string& filename) {
    if (find_file(filename)) {
        Out::Error("file with same path already exists");
        return;
    }

    File* new_file = new File(filename, this);
    m_Nodes.push_back(new Node(new_file));
}

std::string Directory::get_dirname() const { return m_Dirname; }

void Directory::set_path(const std::string& new_path) { m_Path = new_path; }

void Directory::list(bool all_flag) const {
    std::string list_all = "";
    for (Node* node : m_Nodes) {
        if (node->hidden()) {
            if (!all_flag) continue;
            list_all += node->display_name();
        } else {
            list_all += node->display_name();
            if (node->get_type() == NodeType::DIRECTORY_NODE) list_all += "/";
        }
        list_all += " ";
    }

    Out::Log(list_all);
    Out::Log(Terminal::DEFAULT);
}

std::string Directory::path() const { return m_Path; }

void Directory::traverse(const std::string depth_denotation) const {
    if (m_Nodes.size() == 0) return;

    auto pre_end = --m_Nodes.end();
    for (auto iter = m_Nodes.begin(); iter != pre_end; ++iter) {
        if ((*iter)->hidden()) continue;
        Out::Log(depth_denotation + "├── " + (*iter)->display_name());
        Out::Default();
        (*iter)->traverse(depth_denotation + "│   ");
    }
    if ((*pre_end)->hidden()) return;
    Out::Log(depth_denotation + "└── " + (*pre_end)->display_name());
    Out::Default();
    (*pre_end)->traverse(depth_denotation + "    ");
}

bool Directory::has_ancestor(Node* node) {
    if (node->get_type() == NodeType::FILE_NODE) return false;

    for (Directory* iter = this;; iter = iter->parent()) {
        if (iter == node->get_data().directory) {
            return true;
        }
        if (iter == iter->parent()) break;
    }
    return false;
}

bool Directory::empty() const { return ((int)m_Nodes.size() == 0); }

// <------Destructor-------->
Directory::~Directory() {
    for (Node* node : m_Nodes) delete node;
}
