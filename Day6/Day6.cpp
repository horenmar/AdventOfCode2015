#include <vector>
#include <iostream>
#include <string>
#include <regex>
#include <cassert>

enum class ops {
    flip,
    off,
    on,
};

struct command {
    int bx, by, ex, ey;
    ops op;
};

command parse_line(const std::string& str) {
    std::regex command_regex("turn on|turn off|toggle");
    std::regex numbers_regex(R"a(\b\d+\b)a");

    std::sregex_iterator numbers(begin(str), end(str), numbers_regex);
    std::sregex_iterator numbers_end;

    int bx = std::stoi((*numbers++).str());
    int by = std::stoi((*numbers++).str());
    int ex = std::stoi((*numbers++).str());
    int ey = std::stoi((*numbers++).str());

    if (str.find("turn on") != std::string::npos) {
        return { bx, by, ex, ey, ops::on };
    }
    if (str.find("turn off") != std::string::npos) {
        return {bx, by, ex, ey, ops::off};
    }
    if (str.find("toggle") != std::string::npos) {
        return {bx, by, ex, ey, ops::flip};
    }
    
    assert(false && "invalid line");
}

using light_field = std::vector<std::vector<int>>;

static const int light_on = 1;
static const int light_off = 0;

// For easy:
//void on(int bx, int by, int ex, int ey, light_field& lights) {
//    for (int x = bx; x <= ex; ++x) {
//        for (int y = by; y <= ey; ++y) {
//            lights[x][y] = light_on;
//        }
//    }
//}
//
//void off(int bx, int by, int ex, int ey, light_field& lights) {
//    for (int x = bx; x <= ex; ++x) {
//        for (int y = by; y <= ey; ++y) {
//            lights[x][y] = light_off;
//        }
//    }
//}
//
//void flip(int bx, int by, int ex, int ey, light_field& lights) {
//    for (int x = bx; x <= ex; ++x) {
//        for (int y = by; y <= ey; ++y) {
//            lights[x][y] ^= light_on;
//        }
//    }
//}

// For hard:
void on(int bx, int by, int ex, int ey, light_field& lights) {
    for (int x = bx; x <= ex; ++x) {
        for (int y = by; y <= ey; ++y) {
            lights[x][y] += light_on;
        }
    }
}

void off(int bx, int by, int ex, int ey, light_field& lights) {
    for (int x = bx; x <= ex; ++x) {
        for (int y = by; y <= ey; ++y) {
            lights[x][y] = std::max(lights[x][y] - 1, 0);
        }
    }
}

void flip(int bx, int by, int ex, int ey, light_field& lights) {
    for (int x = bx; x <= ex; ++x) {
        for (int y = by; y <= ey; ++y) {
            lights[x][y] += 2 * light_on;
        }
    }
}


void perform_command(const command& cmd, light_field& lights) {
    switch (cmd.op) {
    case ops::flip:
        flip(cmd.bx, cmd.by, cmd.ex, cmd.ey, lights);
        break;
    case ops::on:
        on(cmd.bx, cmd.by, cmd.ex, cmd.ey, lights);
        break;
    case ops::off:
        off(cmd.bx, cmd.by, cmd.ex, cmd.ey, lights);
        break;
    default:
        assert(false && "invalid cmd");
    }
}

int main() {
    light_field lights(1000, std::vector<int>(1000));

    std::string line;
    while (std::getline(std::cin, line) && line != "") {
        perform_command(parse_line(line), lights);
    }

    int total = 0;
    for (const auto& col : lights) {
        for (const auto& l : col) {
            total += l;
        }
    }

    std::cout << total << std::endl;
}