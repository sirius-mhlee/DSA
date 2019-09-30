#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

class extended_euclidean
{
public:
	long long gcd;
	long long lcm;
	long long x0;
	long long y0;

public:
	extended_euclidean()
		: gcd(0), lcm(0), x0(0), y0(0)
	{}

public:
	void process(long long a, long long b)
	{
		if (a < b) swap(a, b);

		tie(gcd, x0, y0) = inner_process(a, b);
		lcm = a * b / gcd;
	}

	tuple<long long, long long, long long> inner_process(long long a, long long b)
	{
		if (b == 0) return make_tuple(a, 1, 0);

		long long g, x, y;
		tie(g, x, y) = inner_process(b, a % b);

		return make_tuple(g, y, x - (a / b) * y);
	}
};

//extended_euclidean ee;
//ee.process(a, b);