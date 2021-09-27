#pragma once
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
	Directory(Directory* parentDir, const std::string& dirname) {
		m_parent = parentDir;
		m_dirname = dirname;	
	}

	bool find_file(const std::string& filename) {
		for (uint i = 0; i < m_files.length(); ++i) {
			if (m_files[i]->__str__() == filename) {
				return true;
			}
		}

		return false;
	}

	bool find_directory(const std::string& dirname) {
		return false;
	}

	void make_dir(const std::string& dirname) {
		if (find_directory(dirname)) {
			// LOG.ERROR("directory with same path already exists");
			return;
		} 

		Directory* new_dir = new Directory(this, dirname); 
		m_directories.append(new_dir);
	}

	void touch(const std::string& filename) {
		if (find_file(filename)) {
			// LOG.ERROR("file with same path already exists");
			return;
		}

		File* new_file = new File(filename);
		m_files.append(new_file);
	}

	~Directory() {
		delete &m_files;
		delete &m_directories;
	}
};