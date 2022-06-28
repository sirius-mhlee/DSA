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
class rotating_calipers
{
public:
    value_type result;

public:
    rotating_calipers(const vector<geometry::point<value_type>>& point_list)
        : result(0)
    {
        int p1_curr_idx = 0;
        int p2_curr_idx = 1;

        while (p1_curr_idx < (int)point_list.size())
        {
            int p1_next_idx = (p1_curr_idx + 1) % (int)point_list.size();
            int p2_next_idx = (p2_curr_idx + 1) % (int)point_list.size();

            while (geometry_helper::ccw<value_type>(point_list[p1_curr_idx], point_list[p1_next_idx], geometry::point<value_type>(point_list[p1_curr_idx].x + (point_list[p2_next_idx].x - point_list[p2_curr_idx].x), point_list[p1_curr_idx].y + (point_list[p2_next_idx].y - point_list[p2_curr_idx].y))) > 0)
            {
                p2_curr_idx = p2_next_idx;
                p2_next_idx = (p2_curr_idx + 1) % (int)point_list.size();
            }

            result = max(result, geometry_helper::point_dist_square<value_type>(point_list[p1_curr_idx], point_list[p2_curr_idx]));

            p1_curr_idx++;
        }
    }
};

//rotating_calipers<int> rc(point_list);
//int ret = rc.result;