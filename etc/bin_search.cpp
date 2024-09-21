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

using namespace std;

template<typename value_type>
class bin_search
{
public:
    value_type result;

public:
    bin_search(value_type lo, value_type hi)
        : result(0)
    {
        while (hi - lo >= 2)
        {
            value_type mid = (lo + hi) / 2;

            if (check(mid))
            {
                hi = mid;
            }
            else
            {
                lo = mid;
            }
        }

        for (value_type x = lo; x <= hi; x++)
        {
            if (check(x))
            {
                result = x;
                break;
            }
        }
    }

public:
    bool check(value_type mid)
    {
        if (mid)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

//bin_search<long long> bs(lo, hi);
//long long ret = bs.result;