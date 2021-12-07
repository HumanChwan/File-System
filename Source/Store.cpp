#include "../Header/Store.h"

#include <fstream>

std::string FS::getHashedPassword(const std::string& user) {
    std::ifstream f_in("Data/" + user + ".fs");
    if (f_in.fail()) {
        std::ofstream f_out("Data/" + user + ".fs", std::ios::out);
        f_out.close();
        throw("User does not exist.");
    }

    std::string hashedPassword;
    getline(f_in, hashedPassword);
    f_in.close();

    return hashedPassword;
}
// void FS::
void FS::Parser() {}
void FS::Save(const std::string& user, const std::string& hash) {
    std::ofstream f_out("Data/" + user + ".fs", std::ios::out);
    f_out << hash;
    f_out.close();
}