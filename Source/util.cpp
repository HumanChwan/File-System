#include "../Header/util.h"

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
