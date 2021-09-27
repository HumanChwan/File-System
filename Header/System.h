#ifndef SYSTEM
#define SYSTEM

#include <string>

#include "Directory.h"
#include "Command.h"
#include "Out.h"

class System {
	Directory *root;
	bool live;

	Directory* present;

public:
	System();

	void init();

	~System();
};

#endif
