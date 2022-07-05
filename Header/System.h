#ifndef SYSTEM
#define SYSTEM

#include <string>

#include "Directory.h"
#include "Out.h"

class Command;

class System {
   private:
    Directory* m_Root;
    bool m_Live;
    std::string m_Username;
    std::string m_Computer;
    std::string m_Hashed_password;
    bool m_Logged_in;

   public:
    Directory* present;
    System();

    void init();

    std::string get_user() const;
    void set_user(const std::string& user);
    std::string get_hashed_password() const;
    void set_hashed_password(const std::string& hash);
    bool is_logged_in();
    void toggle_login_status();
    Directory* root() const;
    void reset(Directory* root);

    bool move_to_dir(const std::string& dirname);
    bool move_to_dir(Directory* directory);
    void move_to_root();

    void exit();

    ~System();
};

#endif
