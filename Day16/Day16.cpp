#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

struct aunt {
    int number       = -1;
    int children     = -1;
    int cats         = -1;
    int samoyeds     = -1;
    int pomeranians  = -1;
    int akitas       = -1;
    int vizslas      = -1;
    int goldfish     = -1;
    int trees        = -1;
    int cars         = -1;
    int perfumes     = -1;
};

aunt parse_line(const std::string& str) {
    std::stringstream ss(str);
    aunt auntie;
    std::string temp_str;
    int number;
    char ignore;
    // Aunt xx:
    // temp_str >> number >> ignore
    ss >> temp_str >> number >> ignore;
    auntie.number = number;

    do {
        ss >> temp_str >> number >> ignore;
        if (temp_str == "children:") {
            auntie.children = number;
        } else if (temp_str == "cats:") {
            auntie.cats = number;
        } else if (temp_str == "samoyeds:") {
            auntie.samoyeds = number;
        } else if (temp_str == "pomeranians:") {
            auntie.pomeranians = number;
        } else if (temp_str == "akitas:") {
            auntie.akitas = number;
        } else if (temp_str == "vizslas:") {
            auntie.vizslas = number;
        } else if (temp_str == "goldfish:") {
            auntie.goldfish = number;
        } else if (temp_str == "trees:") {
            auntie.trees = number;
        } else if (temp_str == "cars:") {
            auntie.cars = number;
        } else if (temp_str == "perfumes:") {
            auntie.perfumes = number;
        } else {
            assert(false && "parse error");
        }
    } while (ss);
    return auntie;
}

int main() {
    std::string line;
    std::vector<aunt> aunties;
    while (std::getline(std::cin, line) && line != "") {
        aunties.push_back(parse_line(line));
    }

    // easier than making the constructor :-)
    aunt target_aunt;
    target_aunt.number = 0;
    target_aunt.children = 3;
    target_aunt.cats = 7;
    target_aunt.samoyeds = 2;
    target_aunt.pomeranians = 3;
    target_aunt.akitas = 0;
    target_aunt.vizslas = 0;
    target_aunt.goldfish = 5;
    target_aunt.trees = 3;
    target_aunt.cars = 2;
    target_aunt.perfumes = 1;

    auto it = end(aunties);
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.children == target_aunt.children || auntie.children == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.cats == target_aunt.cats || auntie.cats == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.samoyeds == target_aunt.samoyeds || auntie.samoyeds == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.pomeranians == target_aunt.pomeranians || auntie.pomeranians == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.akitas == target_aunt.akitas || auntie.akitas == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.vizslas == target_aunt.vizslas || auntie.vizslas == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.goldfish == target_aunt.goldfish || auntie.goldfish == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.trees == target_aunt.trees || auntie.trees == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.cars == target_aunt.cars || auntie.cars == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.perfumes == target_aunt.perfumes || auntie.perfumes == -1; });

    assert(std::distance(begin(aunties), it) == 1 && "Too many aunts remain.");
    std::cout << "Easy: " << aunties[0].number << std::endl;

    it = end(aunties);
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.children == target_aunt.children || auntie.children == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.cats > target_aunt.cats || auntie.cats == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.samoyeds == target_aunt.samoyeds || auntie.samoyeds == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.pomeranians < target_aunt.pomeranians || auntie.pomeranians == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.akitas == target_aunt.akitas || auntie.akitas == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.vizslas == target_aunt.vizslas || auntie.vizslas == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.goldfish < target_aunt.goldfish || auntie.goldfish == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.trees > target_aunt.trees || auntie.trees == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.cars == target_aunt.cars || auntie.cars == -1; });
    it = std::partition(begin(aunties), it, [&](const aunt& auntie) {return auntie.perfumes == target_aunt.perfumes || auntie.perfumes == -1; });

    assert(std::distance(begin(aunties), it) == 1 && "Too many aunts remain.");
    std::cout << "Hard: " << aunties[0].number << std::endl;

}