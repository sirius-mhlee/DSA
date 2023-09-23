#include <iostream>
#include <cassert>
#include <cmath>
#include <complex>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>

using namespace std;

namespace math_helper
{
    template<typename value_type>
    vector<value_type> get_divisor_list(const value_type num)
    {
        vector<value_type> divisor_list{1};

        for (value_type divisor_num = 2; divisor_num <= num; divisor_num++)
        {
            if ((num % divisor_num) == 0)
            {
                divisor_list.push_back(divisor_num);
            }
        }

        return divisor_list;
    }
};

//vector<long long> divisor_list = math_helper::get_divisor_list<long long>(num);

namespace math_helper
{
    template<typename value_type>
    value_type greatest_common_divisor(const vector<value_type>& num_list)
    {
        value_type ret = num_list.front();

        for (value_type num : num_list)
        {
            extended_euclidean<value_type> ee(ret, num);
            ret = ee.gcd;
        }

        return ret;
    }
};

//int gcd = math_helper::greatest_common_divisor<int>(num_list);

namespace math_helper
{
    template<typename value_type>
    value_type least_common_multiple(const vector<value_type>& num_list)
    {
        value_type ret = num_list.front();

        for (value_type num : num_list)
        {
            extended_euclidean<value_type> ee(ret, num);
            ret = ee.lcm;
        }

        return ret;
    }
}

//int lcm = math_helper::least_common_multiple<int>(num_list);