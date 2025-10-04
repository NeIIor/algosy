#include <iostream>

int main() {
    int          n;
    long long k, l;

    std::cin >> n >> k >> l;

    for (long long pos     = k;  pos <= l; pos++) {
         long long cur_pos = pos;
         int       level   = n;
        

        while (level > 1) {

            long long prev_len = (1LL << (level - 1)) - 1;

            if (cur_pos == 1) {
                std::cout << char('a' + level - 1);
                break;

            } else if (cur_pos <= 1 + prev_len) {
                cur_pos--;
                level  --;
                
            } else {
                cur_pos -= (1 + prev_len);
                level   --;
            }
        }

        if (level == 1) {
            std::cout << 'a';
        }
    }

    std::cout << std::endl;

    return 0;
}