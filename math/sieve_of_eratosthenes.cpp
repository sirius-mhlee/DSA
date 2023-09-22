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

template<typename value_type>
class sieve_of_eratosthenes
{
public:
	vector<bool> is_prime;

public:
	sieve_of_eratosthenes(value_type limit)
		: is_prime()
	{
		is_prime.assign(limit + 1, true);

		is_prime[0] = false;
		is_prime[1] = false;
		for (value_type i = 2; i * i <= limit; i++)
		{
			if (is_prime[i])
			{
				for (value_type j = i * i; j <= limit; j += i)
				{
					is_prime[j] = false;
				}
			}
		}
	}

public:
    vector<value_type> get_prime_list(value_type start, value_type end)
    {
        vector<value_type> prime_list;

        for (value_type i = start; i <= end; i++)
		{
			if (is_prime[i])
			{
				prime_list.push_back(i);
			}
		}

        return prime_list;
    }
};

//sieve_of_eratosthenes<int> sv(N);
//bool is_prime = sv.is_prime[a];
//vector<int> prime_list = sv.get_prime_list(s, e);