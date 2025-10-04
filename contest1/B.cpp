#include <vector>
#include <iostream>
#include <algorithm>

int main () {
    size_t n = 0;
    std::cin >> n;

    std::vector<size_t> sum(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> sum[i];
    }

    size_t min_sum = 0;
    for (size_t elem : sum) {
        if (min_sum + 1 < elem) {
            std::cout << min_sum + 1 << std::endl;
            return 0;
        } else {
            min_sum += elem;
        }
    }
    std::cout << min_sum + 1 << std::endl;
    return 0;
}