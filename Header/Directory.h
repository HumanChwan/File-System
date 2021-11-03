
#ifndef DIRECTORY
#define DIRECTORY

#include <string>
#include <vector>

#include "File.h"
#include "Node.h"
#include "Out.h"

class Directory {
   private:
    std::string m_Dirname;
    Directory* m_Parent;
    // std::vector<File*> m_files;
    // std::vector<Directory*> m_directories;
    std::vector<Node*> m_Nodes;

    std::string m_Path;

   public:
    Directory(Directory* parentDir, const std::string& dirname);

    bool find_file(const std::string& filename) const;
    File* get_file(const std::string& filename) const;

    bool find_sub_directory(const std::string& dirname) const;

    Directory* get_dir(const std::string& dirname);
    Directory* parent();

    void make_dir(const std::string& dirname);

    void touch(const std::string& filename);

    std::string get_dirname() const;

    void list(bool all_flag) const;

    std::string path() const;

    ~Directory();
};

#endif
