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
    bool m_Hidden;
    std::string m_Name;

   public:
    Node(File* data);
    Node(Directory* data, bool parent = false, bool self = false);
    NodeType get_type() const;
    NodeData get_data() const;
    bool hidden() const;
    std::string get_name() const;
    std::string display_name() const;
    void traverse(const std::string depth_denotion = "") const;
    ~Node();
};

#endif