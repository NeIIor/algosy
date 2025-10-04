#include <iostream>
#include <string>

int main() {
    unsigned long long N, K;
    if (!(std::cin >> N >> K)) return 0;

    const std::string s = std::to_string(K);
    const std::size_t len = s.length();

    unsigned long long prefix = 0;  
    unsigned long long less   = 0;   

    for (std::size_t i = 0; i < len; ++i) {
        int digit = s[i] - '0';
        int start = (i == 0 ? 1 : 0);          

        for (int d = start; d < digit; ++d) {
                unsigned long long pref  = prefix * 10 + d;
                unsigned long long first = pref, next = pref + 1, cnt = 0;

            while (first <= N) {
                unsigned long long upper = (next <= N + 1) ? next : N + 1;
                cnt += upper - first;
                first *= 10;
                next  *= 10;
            }
            
            less += cnt;
        }

        prefix = prefix * 10 + digit;

        if (prefix <= N && (i + 1) < len) {
            ++less;
        }
    }

    std::cout << less + 1 << '\n';
    return 0;
}