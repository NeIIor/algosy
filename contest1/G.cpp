#include <iostream>
#include <vector>
#include <limits>

int N;
long long V;
std::vector<long long> C;

long long best = std::numeric_limits<long long>::max();   

void dfs(int idx, long long curSum, long long curCoins)
{
    if (curSum > V) return;              
    if (idx == N) {    

        if (curSum == V) best = std::min(best, curCoins);
        return;
    }

    dfs(idx + 1, curSum,              curCoins);                       
    dfs(idx + 1, curSum +     C[idx], curCoins + 1);           
    dfs(idx + 1, curSum + 2 * C[idx], curCoins + 2);       
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (!(std::cin >> V >> N)) return 0;
    C.resize(N);
    for (int i = 0; i < N; ++i) std::cin >> C[i];

    long long total = 0;
    for (long long v : C) total += 2 * v; 

    dfs(0, 0, 0);

    if (best != std::numeric_limits<long long>::max())
        std::cout << best << '\n';

    else if (total >= V)
        std::cout << "Change\n";
        
    else
        std::cout << "Impossible\n";

    return 0;
}