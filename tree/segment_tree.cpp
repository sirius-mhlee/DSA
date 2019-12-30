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
class segment_tree
{
public:
	int data_count;

	vector<int> data_idx;
	vector<value_type> data_list;

	vector<value_type> tree;

public:
	segment_tree(int _data_count)
		: data_count(_data_count), data_idx(), data_list(), tree()
	{
		data_idx.assign(data_count, -1);
		data_list.assign(data_count, 0);

		int height = (int)ceil(log2(data_count));
		int tree_size = (1 << (height + 1));
		tree.assign(tree_size, 0);
	}

public:
	void init()
	{
		inner_init(1, 0, data_count - 1);
	}

	value_type inner_init(int node, int start, int end)
	{
		if (start == end)
		{
			data_idx[start] = node;
			return tree[node] = data_list[start];
		}
		else
		{
			int mid = (start + end) / 2;
			return tree[node] = max(inner_init(node * 2, start, mid), inner_init(node * 2 + 1, mid + 1, end));
		}
	}

	void update(int pos, value_type val)
	{
		int node = data_idx[pos];
		tree[node] = val;

		while (node > 1)
		{
			node /= 2;
			tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	value_type query(int pos)
	{
		return inner_query(1, 0, data_count - 1, pos, pos);
	}

	value_type query(int left, int right)
	{
		return inner_query(1, 0, data_count - 1, left, right);
	}

	value_type inner_query(int node, int start, int end, int left, int right)
	{
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return max(inner_query(node * 2, start, mid, left, right), inner_query(node * 2 + 1, mid + 1, end, left, right));
	}
};

//segment_tree<int> seg(N);
//seg.data_list[i] = val;
//seg.init();
//seg.update(pos, val);
//int ret1 = seg.query(pos);
//int ret2 = seg.query(left, right);