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

std::string FS::join(const std::vector<std::string>& str, char split_char) {
    if ((int)str.size() == 0) return "";

    std::string temp = str[0];
    for (int i = 1; i < (int)str.size(); ++i) {
        temp += split_char + str[i];
    }

    return temp;
}
