#include <iostream>
#include <string>
#include <array>
#include <algorithm>

bool rule_1(const std::string& str) {
    for (int i = 0; i < str.size() - 2; ++i) {
        if (str[i] + 2 == str[i + 1] + 1 && str[i + 1] + 1 == str[i + 2]) {
            return true;
        }
    }
    return false;
}

bool rule_2(const std::string& str) {
    return str.find_first_of("iol") == std::string::npos;
}

bool rule_3(const std::string& str) {
    int i = 0;
    bool found_one = false;
    for (; i < str.size() - 1; ++i) {
        if (str[i] == str[i + 1]) {
            found_one = true;
            break;
        }
    }

    for (i += 2; i < str.size() - 1; ++i) {
        if (str[i] == str[i + 1]) {
            return found_one;
        }
    }
    return false;
}

void increment_password(std::string& str) {
    auto revit = rbegin(str);
    while (*revit == 'z') {
        *revit = 'a';
        revit++;
    }
    (*revit)++;
}

static std::array<bool(*)(const std::string&), 3> rules{rule_1, rule_2, rule_3};

std::string get_next_pwd(std::string str) {
    do {
        increment_password(str);
    } while (!std::all_of(begin(rules), end(rules), [&](const auto& func) { return func(str); }));
    return str;
}

int main() {
    std::string password;
    std::getline(std::cin, password);
    std::cout << get_next_pwd(std::move(password)) << std::endl;
    // just feed in the output of easy problem for the hard one.
}