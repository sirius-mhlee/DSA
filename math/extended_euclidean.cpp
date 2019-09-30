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
	extended_euclidean()
		: gcd(0), lcm(0), x0(0), y0(0)
	{}

public:
	void process(value_type a, value_type b)
	{
		if (a < b) swap(a, b);

		tie(gcd, x0, y0) = inner_process(a, b);
		lcm = a * b / gcd;
	}

	tuple<value_type, value_type, value_type> inner_process(value_type a, value_type b)
	{
		if (b == 0) return make_tuple(a, 1, 0);

		value_type g, x, y;
		tie(g, x, y) = inner_process(b, a % b);

		return make_tuple(g, y, x - (a / b) * y);
	}
};

//extended_euclidean<long long> ee;
//ee.process(a, b);