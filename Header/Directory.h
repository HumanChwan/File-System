
#ifndef DIRECTORY
#define DIRECTORY


#include <string>
#include <vector>

#include "File.h"
#include "Out.h"

class Directory {
private:
	std::string m_dirname;
	Directory* m_parent;
	std::vector<File*> m_files;
	std::vector<Directory*> m_directories;

	std::string m_path;

public:
	Directory(Directory* parentDir, const std::string& dirname);

	bool find_file(const std::string& filename) const;

	bool find_sub_directory(const std::string& dirname) const;

	Directory* get_dir(const std::string& dirname);
	Directory* parent();

	void make_dir(const std::string& dirname);

	void touch(const std::string& filename);

	std::string get_dirname() const;

	void list() const;

	std::string path() const;

	~Directory();
};

#endif
