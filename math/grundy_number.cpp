#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <unordered_set>

using namespace std;

template<typename value_type>
class grundy_number
{
public:
	vector<value_type> num;

public:
	grundy_number(value_type n)
		: num()
	{
		num.assign(n + 1, -1);
		
		num[0] = 0;
		for (value_type i = 1; i <= n; i++)
		{
			process(i);
		}
	}

public:
	value_type process(value_type n)
	{
		if (n == 0) return 0;

		value_type& ret = num[n];
		if (ret != -1) return ret;

		unordered_set<value_type> s;

		for (value_type i = 1; i <= n; i++)
		{
			s.insert(process(n - i));
		}

		ret = calculate_minimum_excludant(s);
		return ret;
	}

	value_type calculate_minimum_excludant(const unordered_set<value_type>& s)
	{
		value_type mex = 0;
		while (s.find(mex) != s.end()) mex++;

		return mex;
	}
};

//grundy_number<int> gn(N);
//int number = gn.num[N];