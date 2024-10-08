#include <iostream>
#include <cassert>
#include <cmath>
#include <complex>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <array>

using namespace std;

const int cache_limit = 20 + 1;
array<int, cache_limit> cache{0, 1};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N{};
    cin >> N;

    for (int i = 2; i <= N; i++)
    {
        cache[i] = cache[i - 1] + cache[i - 2];
    }

    cout << cache[N];
    
    return 0;
}
