#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

namespace math_helper
{
	template<typename value_type>
	value_type mod(value_type value, const value_type MOD)
	{
		if (value >= 0) return value % MOD;
		return ((-value / MOD + 1) * MOD + value) % MOD;
	}
};

//long long int mod_value = math_helper::mod<long long int>(value, MOD);