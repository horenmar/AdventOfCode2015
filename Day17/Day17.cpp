#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

int main() {
    std::vector<int> ways(151);
    std::vector<int> containers;
    ways[0] = 1;

    int container;
    while (std::cin >> container) {
        containers.push_back(container);
    }

    std::sort(begin(containers), end(containers));
    
    for (int c : containers) {
        for (int w = 150; w >= c; --w) {
            ways[w] += ways[w - c];
        }
    }
    std::cout << "Easy: " << ways[150] << std::endl;

    // Lets make an ad-hoc combination selector. 
    // Oh god.
    int least = std::numeric_limits<int>::max();
    int how_many = 0;
    for (int k = 1; k < containers.size(); ++k) {
        std::vector<bool> selection(containers.size());
        std::fill(begin(selection), begin(selection) + k, true);
        if (k > least) {
            break;
        }
        do {
            std::vector<int> selected;
            for (int i = 0; i < containers.size(); ++i) {
                if (selection[i]) {
                    selected.push_back(containers[i]);
                }
            }
            if (std::accumulate(begin(selected), end(selected), 0) == 150) {
                least = k;
                how_many++;
            }
        } while (std::prev_permutation(begin(selection), end(selection)));
    }

    std::cout << "Hard: " << how_many << std::endl;
}