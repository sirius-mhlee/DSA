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
class persistent_segment_tree
{
public:
	class node_info
	{
	public:
		value_type val;

		node_info* left;
		node_info* right;

	public:
		node_info(value_type _val, node_info* _left, node_info* _right)
			: val(_val), left(_left), right(_right)
		{}
	};

public:
	int data_count;

	vector<node_info*> node_list;
	vector<node_info*> tree;

public:
	persistent_segment_tree(int _data_count)
		: data_count(_data_count), node_list(), tree()
	{
		tree.push_back(init_node());
	}

	~persistent_segment_tree()
	{
		for (node_info* node : node_list)
		{
			delete node;
		}
	}

public:
	node_info* init_node()
	{
		node_list.push_back(new node_info(0, nullptr, nullptr));
		return node_list.back();
	}

	int update(int pos, value_type value)
	{
		tree.push_back(inner_update(tree.back(), 0, data_count - 1, pos, value));
		return (int)tree.size() - 1;
	}

	node_info* inner_update(node_info* node, int start, int end, int pos, value_type value)
	{
		if (pos < start || end < pos) return node;

		node_info* new_node = init_node();

		if (start == end)
		{
			new_node->val = node->val + value;
		}
		else
		{
			if (node->left == nullptr) node->left = init_node();
			if (node->right == nullptr) node->right = init_node();

			int mid = (start + end) / 2;
			new_node->left = inner_update(node->left, start, mid, pos, value);
			new_node->right = inner_update(node->right, mid + 1, end, pos, value);

			new_node->val = new_node->left->val + new_node->right->val;
		}

		return new_node;
	}

	value_type query(int tree_idx, int pos)
	{
		return inner_query(tree[tree_idx], 0, data_count - 1, pos, pos);
	}

	value_type query(int tree_idx, int left, int right)
	{
		return inner_query(tree[tree_idx], 0, data_count - 1, left, right);
	}

	value_type inner_query(node_info* node, int start, int end, int left, int right)
	{
		if (node == nullptr) return 0;

		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return node->val;

		int mid = (start + end) / 2;
		return inner_query(node->left, start, mid, left, right) + inner_query(node->right, mid + 1, end, left, right);
	}
};

//persistent_segment_tree<long long> pst(1e5 + 1);
//int tree_idx = pst.update(pos, val);
//long long ret1 = pst.query(tree_idx, pos);
//long long ret2 = pst.query(tree_idx, left, right);