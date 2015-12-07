#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <array>

std::string wovels = "aeiou";

bool rule_1_satisfied(const std::string& str) {
    int wovel_count = 0;
    for (char c : str) {
        if (std::find(begin(wovels), end(wovels), c) != end(wovels)) {
            wovel_count++;
            if (wovel_count >= 3) {
                return true;
            }
        }
    }
    return false;
}

bool rule_2_satisfied(const std::string& str) {
    // could be done as an inverted mismatch
    for (int i = 0; i < str.size() - 1; ++i) {
        if (str[i] == str[i + 1]) {
            return true;
        }
    }
    return false;
}

bool rule_3_satisfied(const std::string& str) {
    std::regex reg("ab|cd|pq|xy");
    auto words_begin = std::sregex_iterator(begin(str), end(str), reg);
    auto words_end = std::sregex_iterator();
    return !std::regex_search(str, reg);
}

bool rule_4_satisfied(const std::string& str) {
    for (int i = 0; i < str.size() - 2; ++i) {
        auto substr = str.substr(i, 2);
        if (str.find(substr, i + 2) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool rule_5_satisfied(const std::string& str) {
    // again, could be done as an inverted mismatch
    for (int i = 0; i < str.size() - 2; ++i) {
        if (str[i] == str[i + 2]) {
            return true;
        }
    }
    return false;
}

//std::array<bool(*)(const std::string&), 3> rules{rule_1_satisfied, rule_2_satisfied, rule_3_satisfied};
std::array<bool(*)(const std::string&), 2> rules{ rule_4_satisfied, rule_5_satisfied };

bool is_nice(const std::string& str) {
    return std::all_of(begin(rules), end(rules), [&](auto fptr) { return fptr(str); });
}

int main() {
    std::string line;
    int nice_count = 0;
    while (std::getline(std::cin, line) && line != "") {
        if (is_nice(line)) {
            nice_count++;
        }
    }
    std::cout << nice_count << std::endl;
}