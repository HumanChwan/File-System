#include "../Header/File.h"

#include "../Header/Directory.h"

File::File(const std::string& filename, Directory* parent_dir) {
    m_filename = filename;
    m_parent_directory = parent_dir;
    m_filecontent = "";
}

std::string File::get_filename() const { return m_filename; }

std::string File::content() const { return m_filecontent; }

void File::append_content(const std::string& new_content) {
    m_filecontent += new_content;
}

void File::overwrite_content(const std::string& new_content) {
    m_filecontent = new_content;
}

void File::operator=(std::string& buffer) { m_filecontent = buffer; }

void File::operator+=(std::string& buffer) { m_filecontent += buffer; }
