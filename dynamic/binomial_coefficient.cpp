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

const int cache_limit = 10 + 1;
array<array<int, cache_limit>, cache_limit> cache{};

#ifdef ONLINE_JUDGE
constexpr bool fast_io = true;
#else
constexpr bool fast_io = false;
#endif

int main()
{
	if constexpr (fast_io)
	{
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}

	int N, K;
	cin >> N >> K;

    for (int i = 0; i <= N; i++)
	{
        for (int j = 0; j <= min(i, K); j++)
        {
            if (i == 0 || j == 0 || i == j)
                cache[i][j] = 1;
            else
		        cache[i][j] = cache[i - 1][j - 1] + cache[i - 1][j];
        }
	}

    cout << cache[N][K];
    
    cout << endl;
    return 0;
}
