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

namespace string_helper
{
	bool check_palindrome(const string& word)
	{
		if (word.empty()) return true;

		size_t lo = 0;
		size_t hi = word.size() - 1;

		while (lo < hi)
		{
			if (word[lo] != word[hi]) return false;

			lo++;
			hi--;
		}

		return true;
	}

	bool starts_with(const string& s1, const string& s2)
	{
		if (s1.size() >= s2.size() && s1.compare(0, s2.size(), s2) == 0)
		{
			return true;
		}

		return false;
	}

	template<typename value_type>
	tuple<int, int> find_cycle(const vector<value_type>& sequence, int start, int limit)
	{
		while (start + 1 < limit)
		{
			for (int cycle_size = 1; cycle_size + start < limit; cycle_size++)
			{
				bool check = true;
				for (int i = start; i + cycle_size < limit; i++)
				{
					if (sequence[i] != sequence[i + cycle_size])
					{
						check = false;
						break;
					}
				}

				if (check) return make_tuple(start, cycle_size);
			}

			start++;
		}

		return make_tuple(-1, -1);
	}
};

//bool ret1 = string_helper::check_palindrome(s1);
//bool ret2 = string_helper::starts_with(s1, s2);
//tie(cycle_start, cycle_size) = string_helper::find_cycle(s, p, q);