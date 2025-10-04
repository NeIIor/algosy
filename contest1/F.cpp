#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    if (!(std::cin >> s)) return 0;

    const std::size_t n = s.size();
    std::unordered_set<std::string> seen;

    const unsigned long long total = 1ULL << n;   
    for (unsigned long long mask = 0; mask < total; ++mask) {
        std::vector<char> chosen;
        chosen.reserve(n);

        for (std::size_t i = 0; i < n; ++i) {
            if (mask & (1ULL << i))
                chosen.push_back(s[i]);
        }

        std::sort(chosen.begin(), chosen.end());
        std::string word(chosen.begin(), chosen.end());

        if (seen.insert(word).second)       
            std::cout << word << '\n';       
    }
    return 0;
}