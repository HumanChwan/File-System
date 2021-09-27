#include "../Header/Directory.h"


// <------Constructor-------->
Directory::Directory(Directory* parentDir, const std::string& dirname) {
  m_parent = parentDir;
  m_dirname = dirname;
}

// <------Public Methods-------->
bool Directory::find_file(const std::string& filename) const {
  for (uint i = 0; i < m_files.length(); ++i) {
    if (m_files[i]->__str__() == filename) {
      return true;
    }
  }

  return false;
}

bool Directory::find_directory(const std::string& dirname) const {
  return false;
}

void Directory::make_dir(const std::string& dirname) {
	if (find_directory(dirname)) {
		// LOG.ERROR("directory with same path already exists");
		return;
	}

	Directory* new_dir = new Directory(this, dirname);
	m_directories.append(new_dir);
}

void Directory::touch(const std::string& filename) {
  if (find_file(filename)) {
    // LOG.ERROR("file with same path already exists");
    return;
  }

  File* new_file = new File(filename);
  m_files.append(new_file);
}

// <------Destructor-------->
Directory::~Directory() {
  delete &m_files;
  delete &m_directories;
}
