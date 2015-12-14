#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <numeric>

void preprocess(std::string& line) {
    std::regex positive_reg("gain ");
    std::regex negative_reg("lose ");

    line = std::regex_replace(line, positive_reg, "");
    line = std::regex_replace(line, negative_reg, "-");
}

int get_number(const std::string& line) {
    std::regex find_num(R"a(-?\d+)a");

    auto numbers_start = std::sregex_iterator(begin(line), end(line), find_num);
    std::smatch match = *numbers_start;

    return std::stoi(match.str());
}

int evaluate_seatings(const std::vector<int>& seats, const std::vector<std::vector<int>>& costs) {
    int total = 0;
    for (int i = 0; i < seats.size(); ++i) {
        total += costs[seats[i]][seats[(i + 1) % seats.size()]];
        total += costs[seats[(i + 1) % seats.size()]][seats[i]];
    }
    return total;
}

static const int persons = 8;
static const int seating_size = 9; // 8 for the easy part, we designate ourself as the 9th person

int main() {
    std::string line;
    std::vector<std::vector<int>> costs(seating_size, std::vector<int>(seating_size));
    std::vector<int> seats(seating_size);
    std::iota(begin(seats), end(seats), 0);
    // 8 people, each has 7 changes...
    for (int p = 0; p < persons; ++p) {
        for (int c = 0; c < persons - 1; ++c) {
            std::getline(std::cin, line);
            preprocess(line);
            int change = get_number(line);

            costs[p][(c < p)? c : c + 1] = change;
        }
    }
    int most_happiness = std::numeric_limits<int>::min();
    do {
        most_happiness = std::max(most_happiness, evaluate_seatings(seats, costs));
    } while (std::next_permutation(begin(seats), end(seats)));
    std::cout << most_happiness << std::endl;
}