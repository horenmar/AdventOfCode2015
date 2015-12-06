#include <iostream>
#include <string>

int easy(const std::string& str) {
    int result = 0;
    for (char c : str) {
        if (c == '(') {
            result++;
        } else if (c == ')') {
            result--;
        }
    }
    return result;
}

int hard(const std::string& str) {
    int temp = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            temp++;
        } else if (str[i] == ')') {
            temp--;
        }
        if (temp < 0) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::cout << hard(input) << std::endl;
}