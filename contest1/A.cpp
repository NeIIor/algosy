#include <vector>
#include <iostream>

int main () {
    size_t n = 0;
    std::cin >> n;

    std::vector<int> payments(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> payments[i];
    }

    size_t five = 0;
    size_t init_five = 0;
    for (int payment : payments) {
        if (payment == 5) {
            five++;
        }
        else {
            size_t change = payment - 5;
            if (five * 5 <= change) {
                init_five += (change - five * 5) / 5;
                five = 0;
            }
            else {
                five -= change / 5;
            }
        }
    }
    std::cout << init_five << std::endl;
    return 0;
}