#include <regex>
#include <cassert>
#include <string>
#include <iostream>
#include <cstdint>

int64_t sum_line(const std::string& line) {
    int64_t total = 0;
    std::regex reg(R"a(-?\d+)a");

    auto numbers_start = std::sregex_iterator(begin(line), end(line), reg);
    auto numbers_end = std::sregex_iterator();

    for (auto it = numbers_start; it != numbers_end; ++it) {
        std::smatch match = *it;
        total += std::stoi(match.str());
    }

    return total;
}

size_t find_start(const std::string& str, size_t pos) {
    int square_level = 1;
    int brace_level = 1;
    while (--pos) {
        switch (str[pos]) {
        case ']':
            square_level++;
            break;
        case '[':
            square_level--;
            if (square_level == 0) {
                return pos;
            }
            break;
        case '}':
            brace_level++;
            break;
        case '{':
            brace_level--;
            if (brace_level == 0) {
                return pos;
            }
            break;
        default:
            break;
        }
    }
    assert(false && "unmatched parens");
}

void filter_input(std::string& str) {
    std::size_t pos = 0;
    while (pos != std::string::npos) {
        pos = str.find("red", pos);
        // Did we find it?
        if (pos != std::string::npos) {
            // Find left start
            auto lpos = find_start(str, pos);
            if (str[lpos] == '[') {
                // just skip forward a bit
                pos += 2;
                continue;
            }

            int depth = 1;
            auto rpos = pos;
            // Find right end
            while (depth) {
                ++rpos;
                if (str[rpos] == '{') {
                    depth++;
                }
                if (str[rpos] == '}') {
                    depth--;
                }
            }

            str.erase(lpos, rpos - lpos + 1);
            pos = lpos;
        }
    }
}

int main() {

    int64_t total = 0;
    std::string line;
    std::string full_str;
    full_str.reserve(40000);
    while (std::getline(std::cin, line) && line != "") {
        full_str += line;
    }

    filter_input(full_str);

    total += sum_line(full_str);
    std::cout << total << std::endl;
}