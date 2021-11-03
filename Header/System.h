#ifndef SYSTEM
#define SYSTEM

#include <string>

#include "Directory.h"
#include "Out.h"

class Command;

class System {
   private:
    Directory* root;
    bool live;
    std::string user;

   public:
    Directory* present;
    System();

    void init();

    std::string get_user();

    void move_to_dir(const std::string& dirname);
    void move_to_dir(Directory& directory);
    void move_to_root();

    void exit();

    ~System();
};

#endif
