#include "../Header/Node.h"

#include "../Header/Directory.h"
#include "../Header/File.h"

// <---------Constructors----------->
Node::Node(File* data) {
    m_Parent = false;
    m_Self = false;
    m_Type = NodeType::FILE_NODE;
    m_Data.file = data;
    m_Name = data->get_filename();
    m_Hidden = (m_Name[0] == '.');
}

Node::Node(Directory* data, bool parent, bool self) {
    m_Parent = false;
    m_Self = false;
    m_Type = NodeType::DIRECTORY_NODE;
    m_Data.directory = data;

    if (parent) {
        m_Parent = true;
        m_Name = "..";
    } else if (self) {
        m_Self = true;
        m_Name = ".";
    } else {
        m_Name = data->get_dirname();
    }

    m_Hidden = (m_Name[0] == '.');
}

// <-------Public Methods--------->
std::string Node::get_name() const {
    return m_Name;
}

std::string Node::display_name() const {
    if (m_Type == NodeType::DIRECTORY_NODE) {
        return Terminal::PURPLE + m_Name;
    } else {
        return Terminal::CYAN + m_Name;
    }
}

NodeType Node::get_type() const {
    return m_Type;
}

NodeData Node::get_data() const {
    return m_Data;
}

bool Node::hidden() const {
    return m_Hidden;
}
bool Node::parent() const {
    return m_Parent;
}
bool Node::self() const {
    return m_Self;
}

void Node::traverse(std::string depth_denotation) const {
    if (m_Type == NodeType::DIRECTORY_NODE)
        m_Data.directory->traverse(depth_denotation);
}

// <------Destructor-------->
Node::~Node() {
    switch (m_Type) {
        case NodeType::FILE_NODE:
            delete m_Data.file;
            break;

        case NodeType::DIRECTORY_NODE:
            if (!m_Parent && !m_Self)
                delete m_Data.directory;
            break;

        default:
            break;
    }
}