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
#include <vector>

using namespace std;

const int cache_limit = 1000 + 1;
array<int, cache_limit> cache{};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N{};
    cin >> N;

    vector<int> num(N + 1, 0);

    for (int i = 1; i <= N; i++)
    {
        cin >> num[i];
    }

    int result{1};
    
    for (int i = 1; i <= N; i++)
    {
        cache[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (num[i] > num[j])
            {
                cache[i] = max(cache[i], cache[j] + 1);
                result = max(result, cache[i]);
            }
        }
    }

    cout << result;

    return 0;
}
