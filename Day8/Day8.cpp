#include <string>
#include <iostream>
#include <cassert>

size_t in_memory_size(const std::string& str) {
    size_t total = 0;
    bool escape_sequence_active = false;
    for (int i = 0; i < str.size(); ++i) {
        switch (str[i]) {
        case '\\':
            if (escape_sequence_active) {
                // this is the second \, ergo it ended
                escape_sequence_active = false;
            } else {
                // First \ found, skip to the next character.
                escape_sequence_active = true;
                continue;
            }
            case 'x':
                if (escape_sequence_active) {
                    // This is part of hexadecimal escape sequence, skip ahead
                    i += 2;
                }
                escape_sequence_active = false;
                break;
            case '"':
                assert(escape_sequence_active && "We shouldn't find \" without active escape sequence.");
                escape_sequence_active = false;
                break;
        }
        total++;
    }
    return total;
}

inline bool needs_escaping(char c) {
    return c == '\\' || c == '"';
}

size_t encoded_size(const std::string& str) {
    size_t total = 2;
    for (char c : str) {
        if (needs_escaping(c)) {
            total++;
        }
        total++;
    }
    return total;
}

int main() {
    std::string line;

    size_t in_code_total = 0;
    size_t in_memory_total = 0;
    size_t encoded_total = 0;
    while (std::getline(std::cin, line) && line != "") {
        in_code_total += line.size();
        in_memory_total += in_memory_size(std::string{begin(line) + 1, (rbegin(line) + 1).base()});
        encoded_total += encoded_size(line);
    }

    std::cout << "Task 1: " << in_code_total - in_memory_total << '\n';
    std::cout << "Task 2: " << encoded_total - in_code_total << '\n';
}