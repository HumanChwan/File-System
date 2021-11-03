#include "../Header/Out.h"

#include "../Header/System.h"

Out::Out() { std::cout << "\t\tFS - C00LD99D\n\n"; }

void Out::Error(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

void Out::Base_Prompt(const std::string& user, const std::string& path) {
    std::cout << "@" << user << ":" << path << "$ ";
}

void Out::Log(const std::string& message) {
    std::cout << message << "\n" << std::endl;
}
