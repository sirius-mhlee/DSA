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
class rabin_karp
{
public:
	const value_type MOD = 1e9;

public:
	vector<int> result;

public:
	rabin_karp(string text, string pattern)
		: result()
	{
		int text_size = (int)text.size();
		int pattern_size = (int)pattern.size();

		value_type power = 1;
		value_type hash_text = 0;
		value_type hash_pattern = 0;

		for (int i = 0; i <= text_size - pattern_size; i++)
		{
			if (i == 0)
			{
				for (int j = 0; j < pattern_size; j++)
				{
					hash_text = math_helper::mod<value_type>(hash_text + text[pattern_size - 1 - j] * power, MOD);
					hash_pattern = math_helper::mod<value_type>(hash_pattern + pattern[pattern_size - 1 - j] * power, MOD);
					if (j < pattern_size - 1) power = math_helper::mod<value_type>(power * 2, MOD);
				}
			}
			else
			{
				hash_text = math_helper::mod<value_type>(2 * (hash_text - text[i - 1] * power) + text[i + pattern_size - 1], MOD);
			}

			if (hash_text == hash_pattern)
			{
				bool check = true;
				for (int j = 0; j < pattern_size; j++)
				{
					if (text[i + j] != pattern[j])
					{
						check = false;
						break;
					}
				}

				if (check) result.push_back(i);
			}
		}
	}
};

//rabin_karp<long long int> rk(T, P);
//vector<int> ret = rk.result;