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
class fast_combination
{
public:
	value_type mod_value;

	vector<value_type> mod_inv;
	vector<value_type> fact;
	vector<value_type> fact_inv;

public:
	fast_combination(const value_type& limit, const value_type& m)
		: mod_value(m), mod_inv(), fact(), fact_inv()
	{
		mod_inv.assign(limit + 1, 0);
		fact.assign(limit + 1, 0);
		fact_inv.assign(limit + 1, 0);

		mod_inv[1] = 1;
		fact[0] = 1;
		fact[1] = 1;
		fact_inv[0] = 1;
		fact_inv[1] = 1;

		for (value_type i = 2; i <= limit; i++)
		{
			mod_inv[i] = (mod_value - ((mod_value / i) * mod_inv[mod_value % i] % mod_value)) % mod_value;
			fact[i] = (fact[i - 1] * i) % mod_value;
			fact_inv[i] = (fact_inv[i - 1] * mod_inv[i]) % mod_value;
		}
	}

public:
	value_type process(const value_type& n, const value_type& r)
	{
		if (n < 0 || r < 0) return 0;
		if (n < r) return 0;
		if (n == r) return 1;

		return (fact[n] * (fact_inv[r] * fact_inv[n - r] % mod_value)) % mod_value;
	}
};

//fast_combination<long long> fc(N, MOD);
//long long result = fc.process(n, r);