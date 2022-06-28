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
class extended_euclidean
{
public:
    value_type gcd;
    value_type lcm;
    value_type x0;
    value_type y0;

public:
    extended_euclidean(value_type a, value_type b)
        : gcd(0), lcm(0), x0(0), y0(0)
    {
        tie(gcd, x0, y0) = process(a, b);
        lcm = a * b / gcd;
    }

public:
    tuple<value_type, value_type, value_type> process(value_type a, value_type b)
    {
        if (a == 0) return make_tuple(b, 0, 1);

        value_type g, x, y;
        tie(g, x, y) = process(b % a, a);

        return make_tuple(g, y - (b / a) * x, x);
    }
};

//extended_euclidean<long long> ee(a, b);
//long long gcd = ee.gcd;
//long long lcm = ee.lcm;