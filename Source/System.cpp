#include "../Header/System.h"

#include "../Header/Command.h"
#include "../Header/Out.h"

System::System() {
    m_Root = new Directory(nullptr, "root");
    present = m_Root;
    m_Live = true;
    m_Username = "<!Temp User>";
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

Directory* System::root() const { return m_Root; }
std::string System::get_user() const { return m_Username; }
void System::set_user(const std::string& user) { m_Username = user; }
std::string System::get_hashed_password() const { return m_Hashed_password; }
void System::set_hashed_password(const std::string& hash) {
    m_Hashed_password = hash;
}
bool System::is_logged_in() { return m_Logged_in; }
void System::toggle_login_status() { m_Logged_in = !m_Logged_in; }
void System::reset(Directory* root) {
    delete m_Root;
    if (root == nullptr) {
        m_Root = new Directory(nullptr, "root");
        present = m_Root;
        m_Username = "<!Temp User>";
    } else {
        m_Root = root;
        present = m_Root;
    }
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

void System::move_to_root() { present = m_Root; }

void System::exit() {
    Out::Log("Exiting...");
    m_Live = false;
    Out::Log("Exited!");
}

System::~System() { delete m_Root; }
