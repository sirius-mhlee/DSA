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

class kmp
{
public:
	vector<int> failure_function;

	vector<int> result;

public:
	kmp(string text, string pattern)
		: failure_function(), result()
	{
		int text_size = (int)text.size();
		int pattern_size = (int)pattern.size();
		process_failure_function(pattern);

		for (int i = 0, j = 0; i < text_size; i++)
		{
			while (j > 0 && text[i] != pattern[j])
				j = failure_function[j - 1];

			if (text[i] == pattern[j])
			{
				if (j == pattern_size - 1)
				{
					result.push_back(i - pattern_size + 1);
					j = failure_function[j];
				}
				else
				{
					j++;
				}
			}
		}
	}

public:
	void process_failure_function(string pattern)
	{
		int pattern_size = (int)pattern.size();
		failure_function.assign(pattern_size, 0);

		for (int i = 1, j = 0; i < pattern_size; i++)
		{
			while (j > 0 && pattern[i] != pattern[j])
				j = failure_function[j - 1];

			if (pattern[i] == pattern[j])
				failure_function[i] = ++j;
		}
	}
};

//kmp k(T, P);
//vector<int> failure_function = k.failure_function;
//vector<int> ret = k.result;