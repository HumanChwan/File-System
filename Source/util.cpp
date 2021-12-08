#include "../Header/util.h"

#include <cassert>
#include <fstream>

std::vector<std::string> FS::split(const std::string& str, char split_char) {
    std::vector<std::string> a;
    std::string temp = "";
    for (char x : str) {
        if (x == split_char) {
            a.push_back(temp);
            temp = "";
        } else {
            temp += x;
        }
    }
    if (temp != "") a.push_back(temp);

    return a;
}

std::string FS::join(const std::vector<std::string>& str, char split_char) {
    if ((int)str.size() == 0) return "";

    std::string temp = str[0];
    for (int i = 1; i < (int)str.size(); ++i) {
        temp += split_char + str[i];
    }

    return temp;
}

std::string FS::hashIt(const std::string& base) {
    std::string hash = "";

    static int32_t key = 0;
    if (key == 0) {
        std::ifstream f(".env");
        assert(!f.fail());
        f >> key;
        f.close();
    }

    // Printable Characters: 33 - 126
    for (char x : base) {
        hash += (char)((x ^ key) % 94 + 33);
    }

    return hash;
}