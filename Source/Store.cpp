#include "../Header/Store.h"

#include <fstream>

std::string FS::getHashedPassword(const std::string& user) {
    std::ifstream f_in("Data/" + user + FS::EXT);
    if (f_in.fail()) {
        throw("User does not exist.");
    }

    std::string hashedPassword;
    getline(f_in, hashedPassword);
    f_in.close();

    return hashedPassword;
}
Directory* FS::Parser(const std::string& user) { return nullptr; }
void FS::Save(const std::string& user, const std::string& hash,
              const Directory* root) {
    std::ofstream f_out("Data/" + user + FS::EXT, std::ios::out);
    f_out << hash << "\n";

    f_out.close();
}