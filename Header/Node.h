#ifndef FSNode
#define FSNode

#include <string>

class Directory;
class File;

enum class NodeType { FILE_NODE, DIRECTORY_NODE };
union NodeData {
    File* file;
    Directory* directory;
};

class Node {
   private:
    NodeType m_Type;
    NodeData m_Data;
    bool m_Parent;
    bool m_Self;
    std::string m_Name;

   public:
    Node(File* data);
    Node(Directory* data, bool parent = false, bool self = false);
    NodeType get_type() const;
    NodeData get_data() const;
    std::string get_name() const;
    ~Node();
};

#endif