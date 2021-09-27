#ifndef FSFILE
#define FSFILE

#include <string>
#include "Out.h"

class Directory;

class File {
	std::string m_filename;
	Directory* m_parent_directory;

	std::string m_filecontent;
public:
	File(const std::string& filename, Directory* parent_dir);

	std::string get_filename() const;

	std::string content() const;

	void append_content(const std::string& new_content);

	void overwrite_content(const std::string& new_content);
};

#endif
