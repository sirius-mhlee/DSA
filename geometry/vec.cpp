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

	template<typename value_type>
	value_type cross(vec<value_type> a, vec<value_type> b)
	{
		return a.x * b.y - a.y * b.x;
	}
};

//geometry::vec<int> v1(0, 0);
//int ret = geometry::cross(v1, v2);