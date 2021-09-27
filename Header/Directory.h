
#ifndef DIRECTORY
#define DIRECTORY


#include <string>

#include "Array.h"
#include "File.h"


class Directory {
private:
	std::string m_dirname;
	Directory* m_parent;
	Array<File*> m_files;
	Array<Directory*> m_directories;

public:
	Directory(Directory* parentDir, const std::string& dirname);

	bool find_file(const std::string& filename) const;

	bool find_directory(const std::string& dirname) const;

	void make_dir(const std::string& dirname);

	void touch(const std::string& filename);

	~Directory();
};

#endif
