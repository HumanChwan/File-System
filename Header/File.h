#ifndef FSFILE
#define FSFILE

#include <string>

class File {
	std::string m_filename;
public:
	File();

	File(const std::string& filename);

	std::string __str__() const;

	~File();
};

#endif
