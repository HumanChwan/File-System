#include <iostream>
#include <string>

#include "../Header/Directory.h"

constexpr int MONKE = 0;

class System {
	Directory *root;
public:
	System() {
		root = new Directory(nullptr, "root");
	}

	~System() {
		std::cout << "Destructed";
		delete root;
	}
};

int main () {
	System system;
	return MONKE;
}
