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

namespace string_helper
{
    template<typename value_type>
    int find_duplicate_gap(const vector<value_type>& sequence, int start, int limit)
    {
        while (start + 1 < limit)
        {
            for (int duplicate_gap = 1; start + duplicate_gap < limit; duplicate_gap++)
            {
                bool check = true;
                for (int i = start; i + duplicate_gap < limit; i++)
                {
                    if (sequence[i] != sequence[i + duplicate_gap])
                    {
                        check = false;
                        break;
                    }
                }

                if (check) return duplicate_gap;
            }

            start++;
        }

        return -1;
    }
};

//int duplicate_gap = string_helper::find_duplicate_gap(s, p, q);