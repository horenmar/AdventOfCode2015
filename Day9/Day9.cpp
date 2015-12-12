#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <sstream>
#include <map>
#include <limits>
#include <algorithm>


std::map<std::string, int> name_index;
int current_index = 0;
std::vector<std::vector<int>> vec(8, std::vector<int>(8));

void parse_line(const std::string& line) {
    std::stringstream str(line);
    std::string from, to;
    int length;
    char ignore;
    str >> from >> to;
    str >> to >> ignore >> length;
    auto it1 = name_index.find(from);
    if (it1 == end(name_index)) {
        name_index[from] = current_index++;
    }
    auto it2 = name_index.find(to);
    if (it2 == end(name_index)) {
        name_index[to] = current_index++;
    }

    vec[name_index[from]][name_index[to]] = length;
    vec[name_index[to]][name_index[from]] = length;
}

// easy:
//int best = std::numeric_limits<int>::max();
// hard:
int best = std::numeric_limits<int>::min();

int evaluate(const std::vector<int>& locations) {
    int total = 0;
    for (int i = 0; i < locations.size() - 1; ++i) {
        total += vec[locations[i]][locations[i + 1]];
    }
    return total;
}

void recurse(std::vector<int>& locations) {
    if (locations.size() == 8)  {
// easy:
//        best = std::min(best, evaluate(locations));
// hard:
        best = std::max(best, evaluate(locations));
        return;
    }
    for (int i = 0; i < 8; ++i) {
        if (std::find(begin(locations), end(locations), i) == end(locations)) {
            locations.push_back(i);
            recurse(locations);
            locations.pop_back();
        }
    }
}

int main() {
    std::string line;
    while (std::getline(std::cin, line) && line != "") {
        parse_line(line);
    }

    std::vector<int> locations;
    recurse(locations);
    std::cout << best << std::endl;
}