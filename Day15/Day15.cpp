#include <iostream>
#include <vector>
#include <array>
#include <limits>

struct ingredient {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};


static ingredient ingredients[] = {
    {3, 0, 0, -3, 2},
    {-3, 3, 0, 0, 9},
    {-1, 0, 4, 0, 1},
    {0, 0, -2, 2, 8},
};

int score_cookie(const std::array<int, 4>& amounts) {
    ingredient subtotals = { 0, 0, 0, 0, 0 };
    for (int i = 0; i < 4; ++i) {
        subtotals.capacity += amounts[i] * ingredients[i].capacity;
        subtotals.durability += amounts[i] * ingredients[i].durability;
        subtotals.flavor += amounts[i] * ingredients[i].flavor;
        subtotals.texture += amounts[i] * ingredients[i].texture;
    }
    subtotals.capacity = std::max(0, subtotals.capacity);
    subtotals.durability = std::max(0, subtotals.durability);
    subtotals.flavor = std::max(0, subtotals.flavor);
    subtotals.texture = std::max(0, subtotals.texture);

    return subtotals.capacity * subtotals.durability * subtotals.flavor * subtotals.texture;
}

bool is_valid_cookie(const std::array<int, 4>& amounts) {
    return 500 == (ingredients[0].calories * amounts[0] +
                   ingredients[1].calories * amounts[1] +
                   ingredients[2].calories * amounts[2] +
                   ingredients[3].calories * amounts[3]);
}

int best_cookie() {
    std::array<int, 4> amounts = {};
    int best_score = std::numeric_limits<int>::min();
    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100 - i; ++j) {
            for (int k = 0; k <= 100 - i - j; k++) {
                amounts[0] = i;
                amounts[1] = j;
                amounts[2] = k;
                amounts[3] = 100 - i - j - k;
                if (is_valid_cookie(amounts)) { // remove for easy part
                    best_score = std::max(best_score, score_cookie(amounts));
                }
            }
        }
    }
    return best_score;
}

int main() {
    std::cout << best_cookie() << std::endl;
}