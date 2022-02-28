#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>

using namespace std;

namespace geometry_helper
{
	using namespace geometry;

	template<typename value_type>
	value_type dot(vec<value_type> a, vec<value_type> b)
	{
		return a.x * b.x + a.y * b.y;
	}

	template<typename value_type>
	value_type cross(vec<value_type> a, vec<value_type> b)
	{
		return a.x * b.y - a.y * b.x;
	}

	template<typename value_type>
	value_type point_dist_square(point<value_type> a, point<value_type> b)
	{
		value_type diff_x = a.x - b.x;
		value_type diff_y = a.y - b.y;

		return (diff_x * diff_x) + (diff_y * diff_y);
	}

	template<typename value_type>
	value_type point_dist(point<value_type> a, point<value_type> b)
	{
		return sqrt(point_dist_square(a, b));
	}

	template<typename value_type>
	value_type perpendicular_dist(point<value_type> line_a, point<value_type> line_b, point<value_type> c)
	{
		value_type dot1 = dot(vec<value_type>(line_a, line_b), vec<value_type>(line_a, c));
		value_type dot2 = dot(vec<value_type>(line_b, line_a), vec<value_type>(line_b, c));

		value_type result = -1;
		if (dot1 * dot2 > static_cast<value_type>(EPS))
		{
			result = abs(cross(vec<value_type>(line_a, line_b), vec<value_type>(line_a, c))) / point_dist(line_a, line_b);
		}
		return result;
	}

	template<typename value_type>
	int ccw(point<value_type> a, point<value_type> b, point<value_type> c)
	{
		value_type val = cross(vec<value_type>(a, b), vec<value_type>(a, c));

		if (val > static_cast<value_type>(EPS)) return 1;
		else if (val < -static_cast<value_type>(EPS)) return -1;
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
			int ccw_abcd = ccw_abc * ccw_abd;
			int ccw_cdab = ccw(c, d, a) * ccw(c, d, b);
			if (ccw_cdab < 0)
			{
				if (ccw_abcd == 0) return 1;
				return 2;
			}
			else if (ccw_cdab == 0) return 1;
			return 0;
		}
	}

	template<typename value_type>
	value_type area(vector<point<value_type>> point_list)
	{
		value_type result = 0;
		for (int i = 1; i < (int)point_list.size() - 1; i++)
		{
			result += cross(vec<value_type>(point_list[0], point_list[i]), vec<value_type>(point_list[0], point_list[i + 1]));
		}

		return result;
	}

	template<typename value_type>
	bool check_convex(vector<point<value_type>> point_list)
	{
		bool positive = false;
		bool negative = false;

		for (int i = 0; i < (int)point_list.size(); i++)
		{
			int j = (i + 1) % (int)point_list.size();
			int k = (i + 2) % (int)point_list.size();

			int ccw_result = ccw(point_list[i], point_list[j], point_list[k]);
			if (ccw_result > 0) positive = true;
			else if (ccw_result < 0) negative = true;

			if (positive && negative) return false;
		}
		return true;
	}

	template<typename value_type>
	bool check_point_include_ccw(vector<point<value_type>> point_list, point<value_type> check_point)
	{
		bool positive = false;
		bool negative = false;

		for (int i = 0; i < (int)point_list.size(); i++)
		{
			int j = (i + 1) % (int)point_list.size();

			int ccw_result = ccw(point_list[i], point_list[j], check_point);
			if (ccw_result >= 0) positive = true;
			else if (ccw_result < 0) negative = true;

			if (positive && negative) return false;
		}
		return true;
	}

	template<typename value_type>
	bool check_point_include_raycast(vector<point<value_type>> point_list, point<value_type> check_point)
	{
		int check_value = 0;

		for (int i = 0; i < (int)point_list.size(); i++)
		{
			int j = (i + 1) % (int)point_list.size();

			point<value_type> point_target(check_point.x + INF, check_point.y + 1);

			int intersect_count_ret = intersect_count(point_list[i], point_list[j], check_point, point_target);
			if (intersect_count_ret == 1 || intersect_count_ret == 8)
			{
				return true;
			}
			else if (intersect_count_ret == 2)
			{
				check_value++;
			}
		}

		if (check_value % 2) return true;
		return false;
	}
};

//int dot_ret = geometry_helper::dot<int>(v1, v2);
//int cross_ret = geometry_helper::cross<int>(v1, v2);
//int point_dist_ret = geometry_helper::point_dist<int>(p1, p2);
//float perpendicular_dist_ret = geometry_helper::perpendicular_dist<float>(l1, l2, p);
//int ccw_ret = geometry_helper::ccw<int>(p1, p2, p3);
//bool intersect_ret = geometry_helper::intersect<int>(p1, p2, p3, p4);
//long long area_ret = geometry_helper::area<long long>(point_list);
//bool check_convex_ret = geometry_helper::check_convex<int>(point_list);
//bool check_point_include_ccw_ret = geometry_helper::check_point_include_ccw<int>(point_list, check_point);
//bool check_point_include_raycast_ret = geometry_helper::check_point_include_raycast<int>(point_list, check_point);
