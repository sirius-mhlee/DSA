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
class merge_sort_tree
{
public:
	int data_count;

	vector<value_type> data_list;

	vector<vector<value_type>> tree;

public:
	merge_sort_tree(int _data_count)
		: data_count(_data_count), data_list(), tree()
	{
		data_list.assign(data_count, 0);

		int height = (int)ceil(log2(data_count));
		int tree_size = (1 << (height + 1));
		tree.assign(tree_size, vector<value_type>());
	}

public:
	void init()
	{
		inner_init(1, 0, data_count - 1);
	}

	void inner_init(int node, int start, int end)
	{
		if (start == end)
		{
			tree[node].push_back(data_list[start]);
		}
		else
		{
			int mid = (start + end) / 2;
			inner_init(node * 2, start, mid);
			inner_init(node * 2 + 1, mid + 1, end);

			merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), back_inserter(tree[node]));
		}
	}

	int query(int left, int right, value_type val)
	{
		return inner_query(1, 0, data_count - 1, left, right, val);
	}

	int inner_query(int node, int start, int end, int left, int right, value_type val)
	{
		if (right < start || end < left) return 0;
		if (left <= start && end <= right)
		{
			return distance(upper_bound(tree[node].begin(), tree[node].end(), val), tree[node].end());
		}

		int mid = (start + end) / 2;
		int left_count = inner_query(node * 2, start, mid, left, right, val);
		int right_count = inner_query(node * 2 + 1, mid + 1, end, left, right, val);

		return left_count + right_count;
	}
};

//merge_sort_tree<long long> ms(N);
//ms.data_list[i] = val;
//ms.init();
//int ret = ms.query(left, right, val);