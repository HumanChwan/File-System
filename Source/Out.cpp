#include "../Header/Out.h"

#include "../Header/System.h"

Out::Out() { std::cout << "\t\tFS - xCaliBer\n\n"; }

void Out::Error(const std::string& message) {
    std::cerr << Terminal::RED << "ERROR: " << Terminal::DEFAULT << message
              << std::endl;
}

void Out::Base_Prompt(const std::string& user, const std::string& path) {
    std::cout << Terminal::BLUE << "@" << user << ":" << Terminal::GREEN << path
              << "$ " << Terminal::DEFAULT;
}

void Out::Log(const std::string& message) { std::cout << message << std::endl; }

void Out::Clear() { std::cout << "\x1b[2J\x1b[1;1H"; }