#include <iostream>
#include <vector>
#include <algorithm>

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

    std::cout << ways[150] << std::endl;

}