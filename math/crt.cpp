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
class crt
{
public:
    value_type result;

public:
    crt(const vector<value_type>& m_value, const vector<value_type>& r_value)
        : result(0)
    {
        value_type prod = 1;
        for (int i = 0; i < (int)m_value.size(); i++)
        {
            prod *= m_value[i];
        }

        for (int i = 0; i < (int)m_value.size(); i++)
        {
            value_type prod_div = prod / m_value[i];
            result += r_value[i] * math_helper::mod_inverse<value_type>(prod_div, m_value[i]) * prod_div;
        }

        result = math_helper::mod<value_type>(result, prod);
    }
};

//crt<long long> c(a, b);
//long long ret = c.result;