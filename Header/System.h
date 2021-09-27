#ifndef SYSTEM
#define SYSTEM

#include <string>

#include "Directory.h"
#include "Out.h"

class Command;

class System {
	Directory *root;
	bool live;


public:
	Directory* present;
	System();

	void init();

	void move_to_dir(const std::string& dirname);

	~System();
};

#endif
