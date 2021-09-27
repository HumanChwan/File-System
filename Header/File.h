#pragma once

#include <string>

class File {
	std::string m_filename;
public:
	File() {
		// std::cout << "New File";
	}

	File(const std::string& filename) {
		m_filename = filename;
	}

	std::string __str__() const {
		return m_filename;
	} 

	~File() {
		// std::cout << "Destructing File :" << m_filename;
	}
};
