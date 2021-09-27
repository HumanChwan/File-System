#include "../Header/Directory.h"

// <------Constructor-------->
Directory::Directory(Directory* parentDir, const std::string& dirname) {
  m_parent = parentDir;
  m_dirname = dirname;

  m_path = "";
  if (parentDir != nullptr) {
    m_path = parentDir->path() + dirname;
  }
  m_path += "/";
}

// <------Public Methods-------->
bool Directory::find_file(const std::string& filename) const {
  for (uint i = 0; i < m_files.size(); ++i) {
    if (m_files[i]->get_filename() == filename) {
      return true;
    }
  }

  return false;
}

bool Directory::find_sub_directory(const std::string& dirname) const {
  for (uint i = 0; i < m_directories.size(); ++i) {
    if (m_directories[i]->get_dirname() == dirname) {
      return true;
    }
  }

  return false;
}

Directory* Directory::get_dir(const std::string& dirname){
  for (uint i = 0; i < m_directories.size(); ++i) {
    if (m_directories[i]->get_dirname() == dirname) {
      return m_directories[i];
    }
  }

  return this;
}

Directory* Directory::parent() {
  return m_parent;
}

void Directory::make_dir(const std::string& dirname) {
	if (find_sub_directory(dirname)) {
		Out::Error("directory with same path already exists");
		return;
	}

	Directory* new_dir = new Directory(this, dirname);
	m_directories.push_back(new_dir);
}

void Directory::touch(const std::string& filename) {
  if (find_file(filename)) {
    Out::Error("file with same path already exists");
    return;
  }

  File* new_file = new File(filename, this);
  m_files.push_back(new_file);
}

std::string Directory::get_dirname() const {
  return m_dirname;
}

void Directory::list() const {
  std::string list_all = "";
  for (File* file : m_files) {
    list_all += file->get_filename() + " ";
  }

  for (Directory* directory : m_directories) {
    list_all += directory->get_dirname() + "/ ";
  }

  Out::Log(list_all);
}

std::string Directory::path() const {
  return m_path;
}

// <------Destructor-------->
Directory::~Directory() {
  for (Directory* directory: m_directories)
    delete directory;
    
  for (File* file: m_files)
    delete file;
}
