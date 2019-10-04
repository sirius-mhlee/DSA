#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

namespace geometry
{
	const double EPS = 1e-9;

	template<typename value_type>
	int ccw(point<value_type> a, point<value_type> b, point<value_type> c)
	{
		value_type val = cross(vec<value_type>(a, b), vec<value_type>(a, c));

		if (val > EPS) return 1;
		else if (val < -EPS) return -1;
		return 0;
	}

	template<typename value_type>
	bool intersect(point<value_type> a, point<value_type> b, point<value_type> c, point<value_type> d)
	{
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);

		int ccw_abc = ccw(a, b, c);
		int ccw_abd = ccw(a, b, d);

		if (ccw_abc == 0 && ccw_abd == 0)
		{
			if (c <= b && a <= d) return true;
			return false;
		}
		else if (ccw_abc == ccw_abd)
		{
			return false;
		}
		else
		{
			int ccw_cdab = ccw(c, d, a) * ccw(c, d, b);
			if (ccw_cdab <= 0) return true;
			return false;
		}
	}

	template<typename value_type>
	int intersect_count(point<value_type> a, point<value_type> b, point<value_type> c, point<value_type> d)
	{
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);

		int ccw_abc = ccw(a, b, c);
		int ccw_abd = ccw(a, b, d);

		if (ccw_abc == 0 && ccw_abd == 0)
		{
			if (c <= b && a <= d)
			{
				if (a == d || c == b) return 1;
				return 8;
			}
			return 0;
		}
		else if (ccw_abc == ccw_abd)
		{
			return 0;
		}
		else
		{
			int ccw_cdab = ccw(c, d, a) * ccw(c, d, b);
			if (ccw_cdab < 0) return 2;
			else if (ccw_cdab == 0) return 1;
			return 0;
		}
	}
};

//geometry::point<int> p1(0, 0);
//bool ret = geometry::intersect(p1, p2, p3, p4);