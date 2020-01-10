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
class sqrt_decomposition
{
public:
	vector<value_type> data_list;

	int bucket_unit_size;
	vector<value_type> bucket;

public:
	sqrt_decomposition(int data_count)
		: data_list(), bucket_unit_size(0), bucket()
	{
		data_list.assign(data_count, 0);
	}

public:
	void init()
	{
		bucket_unit_size = sqrt((int)data_list.size());
		bucket.assign(((int)data_list.size() / bucket_unit_size) + 1, 0);

		for (int i = 0; i < (int)data_list.size(); i++)
		{
			bucket[i / bucket_unit_size] += data_list[i];
		}
	}

	void update(int pos, value_type val)
	{
		value_type diff = val - data_list[pos];

		data_list[pos] = val;
		bucket[pos / bucket_unit_size] += diff;
	}

	value_type query(int left, int right)
	{
		value_type ret = 0;

		while ((left % bucket_unit_size) != 0 && left <= right)
		{
			ret += data_list[left];
			left++;
		}

		while (((right + 1) % bucket_unit_size) != 0 && left <= right)
		{
			ret += data_list[right];
			right--;
		}

		while (left <= right)
		{
			ret += bucket[left / bucket_unit_size];
			left += bucket_unit_size;
		}

		return ret;
	}
};

//sqrt_decomposition<int> sd(N);
//sd.data_list[i] = val;
//sd.init();
//sd.update(pos, val);
//int ret = sd.query(left, right);