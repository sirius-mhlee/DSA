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
	class point
	{
	public:
		value_type x;
		value_type y;

	public:
		point(value_type _x, value_type _y)
			: x(_x), y(_y)
		{}
	};

	template<typename value_type>
	bool operator ==(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		value_type diff_x = lhs.x - rhs.x;
		value_type diff_y = lhs.y - rhs.y;

		if (diff_x > static_cast<value_type>(EPS) || diff_x < -static_cast<value_type>(EPS) || diff_y > static_cast<value_type>(EPS) || diff_y < -static_cast<value_type>(EPS)) return false;
		return true;
	}

	template<typename value_type>
	bool operator !=(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename value_type>
	bool operator <(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		value_type diff_x = rhs.x - lhs.x;
		value_type diff_y = rhs.y - lhs.y;

		if (diff_x > static_cast<value_type>(EPS)) return true;
		else if (diff_x < -static_cast<value_type>(EPS)) return false;
		else if (diff_y > static_cast<value_type>(EPS)) return true;
		return false;
	}

	template<typename value_type>
	bool operator <=(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename value_type>
	bool operator >(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		return (rhs < lhs);
	}

	template<typename value_type>
	bool operator >=(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename value_type>
	value_type dist_square(const point<value_type>& lhs, const point<value_type>& rhs)
	{
		value_type diff_x = lhs.x - rhs.x;
		value_type diff_y = lhs.y - rhs.y;

		return (diff_x * diff_x) + (diff_y * diff_y);
	}
};

//geometry::point<int> p1(0, 0);
//bool ret = (p1 < p2);