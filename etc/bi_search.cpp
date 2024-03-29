#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

template<typename value_type>
class bi_search
{
public:
    value_type result;

public:
    bi_search(value_type lo, value_type hi)
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

//bi_search<long long> bs(lo, hi);
//long long ret = bs.result;