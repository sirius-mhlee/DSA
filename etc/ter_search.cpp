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
class ter_search
{
public:
    value_type result;

public:
    ter_search(value_type lo, value_type hi)
        : result(0)
    {
        while (hi - lo >= 3)
        {
            value_type mid1 = (lo * 2 + hi) / 3;
            value_type mid2 = (lo + hi * 2) / 3;

            if (func(mid1) > func(mid2))
            {
                lo = mid1;
            }
            else
            {
                hi = mid2;
            }
        }

        result = func(lo);
        for (value_type x = lo + 1; x <= hi; x++)
        {
            result = min(result, func(x));
        }
    }

public:
    value_type func(value_type x)
    {
        return (x + 1);
    }
};

//ter_search<long long> ts(lo, hi);
//long long ret = ts.result;