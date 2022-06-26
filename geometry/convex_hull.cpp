#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>

using namespace std;

template<typename value_type>
class convex_hull
{
public:
    vector<geometry::point<value_type>> result;

public:
    convex_hull(vector<geometry::point<value_type>> point_list)
        : result()
    {
        auto it = min_element(point_list.begin(), point_list.end(), [](const geometry::point<value_type>& l, const geometry::point<value_type>& r) {
            value_type diff_x = r.x - l.x;
            value_type diff_y = r.y - l.y;

            if (diff_y > static_cast<value_type>(geometry_constant::EPS)) return true;
            else if (diff_y < -static_cast<value_type>(geometry_constant::EPS)) return false;
            else if (diff_x > static_cast<value_type>(geometry_constant::EPS)) return true;
            return false;
        });

        swap(*it, point_list[0]);

        geometry::point<value_type> base = point_list[0];
        sort(point_list.begin() + 1, point_list.end(), [base](const geometry::point<value_type>& l, const geometry::point<value_type>& r) {
            value_type ccw_value = geometry_helper::ccw<value_type>(base, l, r);
            if (ccw_value == 0)
            {
                return geometry_helper::point_dist_square<value_type>(base, l) < geometry_helper::point_dist_square<value_type>(base, r);
            }

            return ccw_value > 0;
        });

        result.push_back(point_list[0]);
        result.push_back(point_list[1]);

        for (int i = 2; i < (int)point_list.size(); i++)
        {
            geometry::point<value_type> next = point_list[i];

            while ((int)result.size() >= 2)
            {
                geometry::point<value_type> curr = result.back();
                result.pop_back();

                geometry::point<value_type> prev = result.back();

                if (geometry_helper::ccw<value_type>(prev, curr, next) > 0)
                {
                    result.push_back(curr);
                    break;
                }
            }

            result.push_back(next);
        }
    }
};

//convex_hull<int> ch(point_list);
//vector<geometry::point<int>> ret = ch.result;