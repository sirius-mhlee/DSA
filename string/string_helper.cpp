#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

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
};

//bool ret1 = string_helper::check_palindrome(s1);
//bool ret2 = string_helper::starts_with(s1, s2);