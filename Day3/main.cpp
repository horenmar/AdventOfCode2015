#include <string>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <array>

struct pos {
    int x = 0;
    int y = 0;
};

bool operator==(const pos& lhs, const pos& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

namespace std {
template <>
struct std::hash<pos> {
    std::size_t operator()(const pos& hashee) const {
        auto h1 = std::hash<int>{}(hashee.x);
        auto h2 = std::hash<int>{}(hashee.y);
        return (h1 << 10) ^ h2;
    }
};
}

void easy() {
    std::ios_base::sync_with_stdio(false);
    std::unordered_set<pos> houses;
    houses.insert(pos{});
    std::string line;
    pos cposition;
    while (std::getline(std::cin, line) && line != "") {
        for (char c : line) {
            switch (c) {
            case '<':
                cposition.x--;
                break;
            case '>':
                cposition.x++;
                break;
            case '^':
                cposition.y++;
                break;
            case 'v':
                cposition.y--;
                break;
            }
            houses.insert(cposition);
        }
    }
    std::cout << houses.size() << std::endl;
}

void hard() {
    std::ios_base::sync_with_stdio(false);
    std::unordered_set<pos> houses;
    houses.insert(pos{});
    std::string line;
    std::array<pos, 2> cpositions;
    int santa = 0;
    while (std::getline(std::cin, line) && line != "") {
        for (char c : line) {
            switch (c) {
            case '<':
                cpositions[santa].x--;
                break;
            case '>':
                cpositions[santa].x++;
                break;
            case '^':
                cpositions[santa].y++;
                break;
            case 'v':
                cpositions[santa].y--;
                break;
            }
            houses.insert(cpositions[santa]);
            santa ^= 1;
        }
    }
    std::cout << houses.size() << std::endl;

}

int main() {
    hard();
}