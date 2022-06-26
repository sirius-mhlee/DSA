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
class sieve_of_eratosthenes
{
public:
    vector<bool> is_prime;
    vector<value_type> prime_list;

public:
    sieve_of_eratosthenes(value_type limit)
        : is_prime(), prime_list()
    {
        is_prime.assign(limit + 1, true);

        is_prime[0] = false;
        is_prime[1] = false;
        for (value_type i = 2; i * i <= limit; i++)
        {
            if (is_prime[i])
            {
                prime_list.push_back(i);
                for (value_type j = i * i; j <= limit; j += i)
                {
                    is_prime[j] = false;
                }
            }
        }
    }
};

//sieve_of_eratosthenes<int> sv(N);
//bool is_prime = sv.is_prime[a];
//int prime_num = sv.prime_list[0];