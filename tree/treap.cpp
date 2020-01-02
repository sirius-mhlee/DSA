#include <iostream>
#include <random>
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
class treap
{
public:
	class node_info
	{
	public:
		const int MAX_PRIORITY = 32767;

	public:
		value_type val;

		int priority;
		int size;

		node_info* left;
		node_info* right;

	public:
		node_info()
			: val(0), priority(0), size(1), left(nullptr), right(nullptr)
		{
			random_device rd;
			mt19937 mt(rd());
			uniform_int_distribution<int> uid(0, MAX_PRIORITY);

			priority = uid(mt);
		}

	public:
		void calc_size()
		{
			size = 1;
			if (left != nullptr) size += left->size;
			if (right != nullptr) size += right->size;
		}

		void set_left(node_info* node)
		{
			left = node;
			calc_size();
		}

		void set_right(node_info* node)
		{
			right = node;
			calc_size();
		}
	};

public:
	node_info* root_node;
	vector<node_info*> node_list;

public:
	treap()
		: root_node(nullptr), node_list()
	{}

	~treap()
	{
		for (node_info* node : node_list)
		{
			delete node;
		}
	}

public:
	node_info* init_node()
	{
		node_list.push_back(new node_info());
		return node_list.back();
	}

	void insert(value_type value)
	{
		node_info* new_node = init_node();
		new_node->val = value;

		root_node = inner_insert(root_node, new_node);
	}

	node_info* inner_insert(node_info* curr, node_info* node)
	{
		if (curr == nullptr) return node;

		if (curr->priority < node->priority)
		{
			pair<node_info*, node_info*> curr_split = split(curr, node->val);
			node->set_left(curr_split.first);
			node->set_right(curr_split.second);
			return node;
		}

		if (node->val < curr->val)
			curr->set_left(inner_insert(curr->left, node));
		else
			curr->set_right(inner_insert(curr->right, node));

		return curr;
	}

	pair<node_info*, node_info*> split(node_info* curr, value_type value)
	{
		if (curr == nullptr) return make_pair(nullptr, nullptr);

		if (curr->val < value)
		{
			pair<node_info*, node_info*> right_split = split(curr->right, value);
			curr->set_right(right_split.first);
			return make_pair(curr, right_split.second);
		}

		pair<node_info*, node_info*> left_split = split(curr->left, value);
		curr->set_left(left_split.second);
		return make_pair(left_split.first, curr);
	}

	node_info* merge(node_info* left_node, node_info* right_node)
	{
		if (left_node == nullptr) return right_node;
		if (right_node == nullptr) return left_node;

		if (left_node->priority < right_node->priority)
		{
			right_node->set_left(merge(left_node, right_node->left));
			return right_node;
		}

		left_node->set_right(merge(left_node->right, right_node));
		return left_node;
	}

	void erase(value_type value)
	{
		root_node = inner_erase(root_node, value);
	}

	node_info* inner_erase(node_info* curr, value_type value)
	{
		if (curr == nullptr) return curr;

		if (curr->val == value)
		{
			node_info* ret = merge(curr->left, curr->right);
			return ret;
		}

		if (value < curr->val)
			curr->set_left(inner_erase(curr->left, value));
		else
			curr->set_right(inner_erase(curr->right, value));

		return curr;
	}

	value_type kth(int k)
	{
		node_info* kth_node = inner_kth(root_node, k);
		return kth_node->val;
	}

	node_info* inner_kth(node_info* curr, int k)
	{
		int left_size = 0;
		if (curr->left != nullptr) left_size = curr->left->size;

		if (k <= left_size) return inner_kth(curr->left, k);
		if (k == left_size + 1) return curr;
		return inner_kth(curr->right, k - left_size - 1);
	}

	int count_less_than(value_type value)
	{
		return inner_count_less_than(root_node, value);
	}

	int inner_count_less_than(node_info* curr, value_type value)
	{
		if (curr == nullptr) return 0;

		if (curr->val >= value)
			return inner_count_less_than(curr->left, value);

		int left_size = (curr->left ? curr->left->size : 0);
		return left_size + 1 + inner_count_less_than(curr->right, value);
	}
};

//treap<int> tr;
//tr.insert(val);
//int ret1 = tr.kth(k);
//int ret2 = tr.count_less_than(val);