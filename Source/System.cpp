#include "../Header/System.h"

#include "../Header/Command.h"
#include "../Header/Out.h"

System::System() {
    root = new Directory(nullptr, "root");
    present = root;
    m_Live = true;
    m_Username = "~~temp";
    m_Logged_in = false;
}

void System::init() {
    Out();

    while (m_Live) {
        Out::Base_Prompt(get_user(), present->path());
        std::string command;
        getline(std::cin, command);
        Command new_command(this, command);
    }
}

std::string System::get_user() { return m_Username; }
void System::set_user(const std::string& user) { m_Username = user; }
bool System::is_logged_in() { return m_Logged_in; }
void System::toggle_login_status() { m_Logged_in = !m_Logged_in; }
void System::set_hashed_password(const std::string& hash) {
    m_Hashed_password = hash;
}

bool System::move_to_dir(const std::string& dirname) {
    Directory* sub = present->get_dir(dirname);
    if (sub == nullptr) return false;

    present = sub;
    return true;
}

bool System::move_to_dir(Directory* directory) {
    if (directory == nullptr) return false;

    present = directory;
    return true;
}

void System::move_to_root() { present = root; }

void System::exit() {
    Out::Log("Exiting...");
    m_Live = false;
    Out::Log("Exited!");
}

System::~System() { delete root; }
