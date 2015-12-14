#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

struct reindeer {
    std::string name;
    int speed;
    int fly_time;
    int rest_time;
};

int evaluate_reindeer(const reindeer& r, int full_time) {
    const int cycle_time = r.fly_time + r.rest_time;
    const int cycles = full_time / cycle_time;
    int current_position = cycles * r.fly_time * r.speed;
    const int remaining_time = full_time - cycles * cycle_time;
    if (remaining_time >= r.fly_time) {
        return current_position + r.fly_time * r.speed;
    } else {
        return current_position + r.speed * (remaining_time);
    }
}

// Fuck it, no more pretty code.
int simulate_reindeers(const std::vector<reindeer>& reindeers, int full_time) {
    std::vector<int> points(reindeers.size());
    std::vector<int> current_positions(reindeers.size());
    for (int t = 1; t <= full_time; ++t) {
        for (int i = 0; i < reindeers.size(); ++i) {
            current_positions[i] = evaluate_reindeer(reindeers[i], t);
        }
        auto max_pos = *std::max_element(begin(current_positions), end(current_positions));
        for (int i = 0; i < reindeers.size(); ++i) {
            if (current_positions[i] == max_pos) {
                points[i]++;
            }
        }
    }
    return *std::max_element(begin(points), end(points));
}

static const int full_time = 2503;

int main() {

    std::vector<reindeer> reindeers;
    std::vector<int> positions;

    std::string line;
    while (std::getline(std::cin, line) && line != "") {
        std::stringstream str(line);
        std::string name;
        std::string ignore;
        int speed, fly_time, rest_time;
        
        // Name is actually not needed, that should teach me to read questions better. :-D
        // Vixen >> can    >> fly    >> 19    >> km/s   >> for    >> 7        >> seconds, >> but    >> then   >> must   >> rest   >> for    >> 124       >>  seconds.
        // name  >> ignore >> ignore >> speed >> ignore >> ignore >> fly_time >> ignore   >> ignore >> ignore >> ignore >> ignore >> ignore >> rest_time >> ignore
        str >> name >> ignore >> ignore >> speed >> ignore >> ignore >> fly_time >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> rest_time >> ignore;
        reindeer r{name, speed, fly_time, rest_time};

        reindeers.push_back(r);
        positions.push_back(evaluate_reindeer(r, full_time));
    }

    std::cout << "Easy: " << *std::max_element(begin(positions), end(positions)) << std::endl;

    std::cout << "Hard: " << simulate_reindeers(reindeers, full_time) << std::endl;
}