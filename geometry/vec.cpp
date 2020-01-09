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
	using namespace geometry_constant;

	template<typename value_type>
	class vec
	{
	public:
		value_type x;
		value_type y;

	public:
		vec(point<value_type> a, point<value_type> b)
			: x(b.x - a.x), y(b.y - a.y)
		{}
	};
};

//geometry::vec<int> v1(p1, p2);