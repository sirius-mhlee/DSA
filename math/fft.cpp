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
class fft
{
public:
	vector<value_type> result;

public:
	fft(const vector<value_type>& a, const vector<value_type>& b)
		: result()
	{
		vector<complex<double>> complex_a(a.begin(), a.end());
		vector<complex<double>> complex_b(b.begin(), b.end());

		int max_size = (int)max(complex_a.size(), complex_b.size());
		int ceil_log_max_size = (int)ceil(log2(max_size));
		int multiply_size = (1 << (ceil_log_max_size + 1));

		complex_a.resize(multiply_size);
		complex_b.resize(multiply_size);
		vector<complex<double>> complex_result(multiply_size, complex<double>(0.0, 0.0));

		transform(complex_a, false);
		transform(complex_b, false);

		for (int i = 0; i < multiply_size; i++)
		{
			complex_result[i] = complex_a[i] * complex_b[i];
		}

		transform(complex_result, true);

		result.assign(multiply_size, 0);
		for (int i = 0; i < multiply_size; i++)
		{
			result[i] = (value_type)round(complex_result[i].real());
		}
	}

public:
	void transform(vector<complex<double>>& f, bool inverse)
	{
		int size = (int)f.size();

		for (int i = 1, j = 0; i < size; i++)
		{
			int bit = size / 2;
			while (!((j ^= bit) & bit)) bit /= 2;

			if (i < j) swap(f[i], f[j]);
		}

		for (int i = 1; i < size; i *= 2)
		{
			double angle = (inverse ? 1 : -1) * math_helper::PI / i;
			complex<double> w(cos(angle), sin(angle));

			for (int k = 0; k < size; k += i * 2)
			{
				complex<double> w_pow(1.0, 0.0);

				for (int j = 0; j < i; j++)
				{
					complex<double> x = f[k + j];
					complex<double> y = f[k + j + i] * w_pow;

					f[k + j] = x + y;
					f[k + j + i] = x - y;

					w_pow *= w;
				}
			}
		}

		if (inverse)
		{
			for (int i = 0; i < size; i++)
			{
				f[i] /= size;
			}
		}
	}
};

//fft<int> t(a, b);
//vector<int> c = t.result;