#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <functional>

inline int paper_for_box(int height, int width, int len) {
    std::array<int, 3> arr{ height, width, len };
    std::sort(begin(arr), end(arr));
    return 2 * (arr[0] * arr[1] + arr[1] * arr[2] + arr[2] * arr[0]) + arr[0] * arr[1];
}

inline int ribbon_for_box(int height, int width, int len) {
    std::array<int, 3> arr{ height, width, len };
    std::sort(begin(arr), end(arr));
    return 2 * (arr[0] + arr[1]) + std::accumulate(begin(arr), end(arr), 1, std::multiplies<>{});
}

int easy(std::istream& in) {
    std::string str;
    int result = 0;
    while (std::getline(in, str) && str != "") {
        std::stringstream sstream(str);
        std::string temp;
        std::getline(sstream, temp, 'x');
        int a = std::stoi(temp);
        std::getline(sstream, temp, 'x');
        int b = std::stoi(temp);
        std::getline(sstream, temp, 'x');
        int c = std::stoi(temp);

        result += paper_for_box(a, b, c);
    }
    return result;
}

int hard(std::istream& in) {
    std::string str;
    int result = 0;
    while (std::getline(in, str) && str != "") {
        std::stringstream sstream(str);
        std::string temp;
        std::getline(sstream, temp, 'x');
        int a = std::stoi(temp);
        std::getline(sstream, temp, 'x');
        int b = std::stoi(temp);
        std::getline(sstream, temp, 'x');
        int c = std::stoi(temp);

        result += ribbon_for_box(a, b, c);
    }
    return result;
}

int main() {
    std::cout << hard(std::cin) << std::endl;
}