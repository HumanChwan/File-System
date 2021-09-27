#include "../Header/File.h"


File::File() {
 // std::cout << "New File";
}

File::File(const std::string& filename) {
  m_filename = filename;
}

std::string File::__str__() const {
  return m_filename;
}

File::~File() {
  // std::cout << "Destructing File :" << m_filename;
}
