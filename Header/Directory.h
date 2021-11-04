
#ifndef DIRECTORY
#define DIRECTORY

#include <list>
#include <string>

#include "File.h"
#include "Node.h"
#include "Out.h"

class Directory {
   private:
    std::string m_Dirname;
    Directory* m_Parent;
    std::list<Node*> m_Nodes;

    std::string m_Path;

   public:
    Directory(Directory* parentDir, const std::string& dirname);

    bool find_file(const std::string& filename) const;
    File* get_file(const std::string& filename) const;

    bool find_sub_directory(const std::string& dirname) const;
    Directory* get_dir(const std::string& dirname);

    Directory* parent();
    void set_parent_directory(Directory* directory);

    void push_node(Node* node);
    void remove_node(Node* node);

    bool find_node(const std::string& node_name);
    Node* get_node(const std::string& node_name);

    void make_dir(const std::string& dirname);
    void touch(const std::string& filename);

    std::string get_dirname() const;
    void set_path(const std::string& new_path);

    void list(bool all_flag) const;
    std::string path() const;

    ~Directory();
};

#endif
