#include <iostream>

static const int puzzle_input = 36'000'000;

int divisor_sum(const int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            sum += n / i;
        }
    }
    return sum;
}


int adjusted_divisor_sum(const int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            if (n / i < 50) {
                sum += i;
            }
            if (i < 50) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    for (int n = 2; ; ++n) {
        if (divisor_sum(n) * 10 >= puzzle_input) {
            std::cout << "Easy: " << n << '\n';
            break;
        }
    }
    for (int n = 2;; ++n) {
        if (adjusted_divisor_sum(n) * 11 >= puzzle_input) {
            std::cout << "Hard: " << n << '\n';
            break;
        }
    }
}
