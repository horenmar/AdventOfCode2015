#include <iostream>
#include <vector>
#include <numeric>

static const int field_size = 100;

using light_field = std::vector<std::vector<int>>;

light_field make_step(const light_field old_lights) {
    light_field new_lights(field_size, std::vector<int>(field_size));

    for (int r = 0; r < field_size; ++r) {
        for (int c = 0; c < field_size; ++c) {
            int sum = 0;
            // left up
            sum += (r - 1 >= 0 && c - 1 >= 0)? old_lights[r - 1][c - 1]: 0;
            // up
            sum += (r - 1 >= 0)? old_lights[r - 1][c]: 0;
            // up right
            sum += (r - 1 >= 0 && c + 1 < field_size)? old_lights[r - 1][c + 1]: 0;

            // left
            sum += (c - 1 >= 0)? old_lights[r][c - 1]: 0;
            // right
            sum += (c + 1 < field_size)? old_lights[r][c + 1]: 0;

            // left down
            sum += (r + 1 < field_size && c - 1 >= 0)? old_lights[r + 1][c - 1]: 0;
            // down
            sum += (r + 1 < field_size)? old_lights[r + 1][c]: 0;
            // right down
            sum += (r + 1 < field_size && c + 1 < field_size)? old_lights[r + 1][c + 1]: 0;

            if (old_lights[r][c] == 0) {
                new_lights[r][c] = !!(sum == 3);
            } else {
                new_lights[r][c] = (sum == 2 || sum == 3);
            }
        }
    }

    return new_lights;
}

int main() {
    light_field lights(field_size, std::vector<int>(field_size));

    char current;
    for (int r = 0; r < field_size; ++r) {
        for (int c = 0; c < field_size; ++c) {
            std::cin >> current;
            lights[r][c] = (current == '#')? 1 : 0;
        }
    }

    light_field lights_copy = lights;
    for (int i = 0; i < 100; ++i) {
        lights_copy = make_step(lights_copy);
    }

    std::cout << "Easy: " << std::accumulate(begin(lights_copy), end(lights_copy), 0, [](int sum, const auto& vec) {
        return sum + std::accumulate(begin(vec), end(vec), 0);
    }) << std::endl;


    for (int i = 0; i < 100; ++i) {
        // Force the corner lights on before each iteration
        lights[0][0] = 1;
        lights[0][field_size - 1] = 1;
        lights[field_size - 1][0] = 1;
        lights[field_size - 1][field_size - 1] = 1;
        // And iterate
        lights = make_step(lights);
    }

    // Force the corners to 1s again.
    lights[0][0] = 1;
    lights[0][field_size - 1] = 1;
    lights[field_size - 1][0] = 1;
    lights[field_size - 1][field_size - 1] = 1;

    std::cout << "Hard: " << std::accumulate(begin(lights), end(lights), 0, [](int sum, const auto& vec) {
        return sum + std::accumulate(begin(vec), end(vec), 0);
    }) << std::endl;
}