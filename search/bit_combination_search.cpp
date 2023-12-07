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

#include <vector>

using namespace std;

int element_size{};
vector<int> element_list{};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, X;
    cin >> N >> X;

    element_size = N;
    element_list.assign(N, 0);

    for (int i = 0; i < N; i++)
    {
        cin >> element_list[i];
    }

    int match_combination_count = 0;
    for (int element_combination = 1; element_combination < (1 << element_size); element_combination++)
    {
        int value = 0;

        for (int mask_shift = 0; mask_shift < element_size; mask_shift++)
        {
            if (element_combination & (1 << mask_shift))
            {
                value += element_list[mask_shift];
            }
        }

        if (value == X)
        {
            match_combination_count++;
        }
    }

    cout << match_combination_count;

    return 0;
}
