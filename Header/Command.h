#ifndef COMMAND
#define COMMAND

#include <string>
#include <vector>

#include "./Directory.h"

class System;

class Command {
   private:
    System* state;

    Directory* crawl(Directory* start, const std::vector<std::string>& path);
    Directory* crawl(Directory* start, const std::string& path);

   public:
    Command(System* sys_state, const std::string& command);

    void change_directory(const std::vector<std::string>& args);
    void make_directory(const std::vector<std::string>& args);
    void touch(const std::vector<std::string>& args);
    void list(const std::vector<std::string>& args);
    void cat(const std::vector<std::string>& args);
    void move(const std::vector<std::string>& args);
    void tree(const std::vector<std::string>& args);
    void remove(const std::vector<std::string>& args);
    void copy(const std::vector<std::string>& args);
    void clear();
    void exit();
};

#endif
