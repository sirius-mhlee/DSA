#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

namespace bit_helper
{
	template<typename value_type>
	int find_most_left_bit_pos(const value_type& n)
	{
		return log2(n);
	}

	template<typename value_type>
	int find_most_right_bit_pos(const value_type& n)
	{
		return log2(n & (-n));
	}
};

//int mlb = bit_helper::find_most_left_bit_pos(n);
//int mrb = bit_helper::find_most_right_bit_pos(n);