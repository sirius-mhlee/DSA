#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <numeric>
#include <algorithm>
#include <functional>

#include <vector>
#include <map>

using namespace std;

namespace math_helper
{
    const double pi = acos(-1.0);

    template<typename value_type>
    value_type mod(const value_type a, const value_type m)
    {
        if (a >= 0) return a % m;
        return ((-a / m + 1) * m + a) % m;
    }

    template<typename value_type>
    value_type mod_inverse(const value_type a, const value_type m)
    {
        extended_euclidean<value_type> ee(a, m);

        if (ee.gcd != 1) return -1;
        return mod<value_type>(ee.x0, m);
    }

    template<typename value_type>
    map<value_type, int> factorization(value_type num)
    {
        map<value_type, int> factor_map;

        for (value_type factor_num = 2; factor_num * factor_num <= num; factor_num++)
        {
            if (factor_num > num) break;
            if (num % factor_num != 0) continue;

            while (num % factor_num == 0)
            {
                num /= factor_num;
                factor_map[factor_num]++;
            }
        }

        if (num != 1) factor_map[num]++;

        return factor_map;
    }

    template<typename value_type>
    map<value_type, int> factorization(value_type num, const vector<value_type>& prime_list)
    {
        map<value_type, int> factor_map;

        for (value_type prime_num : prime_list)
        {
            if (prime_num > num) break;
            if (num % prime_num != 0) continue;

            while (num % prime_num == 0)
            {
                num /= prime_num;
                factor_map[prime_num]++;
            }
        }

        if (num != 1) factor_map[num]++;

        return factor_map;
    }

    template<typename value_type>
    value_type fast_power(const value_type a, const value_type n)
    {
        if (n == 1) return a;

        value_type ret = fast_power(a, n / 2);
        ret = (ret * ret);
        if (n % 2 != 0) ret = (a * ret);
        return ret;
    }
};

//double pi_value = math_helper::pi;
//long long mod_value = math_helper::mod<long long>(value, mod);
//long long mod_inverse_value = math_helper::mod_inverse<long long>(value, mod);
//map<long long, int> factor_map_naive = math_helper::factorization<long long>(value);
//map<long long, int> factor_map = math_helper::factorization<long long>(value, prime_list);
//long long power_value = math_helper::fast_power<long long>(value, power);