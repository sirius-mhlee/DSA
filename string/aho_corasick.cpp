#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <queue>
#include <map>

using namespace std;

class aho_corasick
{
public:
	class node_info
	{
	public:
		int term;

		map<char, node_info*> child;
		node_info* fail;

	public:
		node_info()
			: term(0), child(), fail(nullptr)
		{}
	};

public:
	node_info* root_node;
	vector<node_info*> node_list;

public:
	aho_corasick()
		: root_node(nullptr), node_list()
	{
		root_node = init_node();
	}

	~aho_corasick()
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

	void process()
	{
		root_node->fail = root_node;

		queue<node_info*> q;
		q.push(root_node);
		while (!q.empty())
		{
			node_info* curr = q.front();
			q.pop();

			for (pair<char, node_info*> node : curr->child)
			{
				char ch = node.first;
				node_info* next = node.second;

				if (curr == root_node)
				{
					next->fail = root_node;
				}
				else
				{
					node_info* curr_fail = curr->fail;
					while (curr_fail != root_node && curr_fail->child[ch] == nullptr)
					{
						curr_fail = curr_fail->fail;
					}

					if (curr_fail->child[ch] != nullptr)
					{
						curr_fail = curr_fail->child[ch];
					}
					next->fail = curr_fail;
				}

				node_info* next_fail = next->fail;
				next->term += next_fail->term;
				q.push(next);
			}
		}
	}

	void insert(string& pattern)
	{
		inner_insert(root_node, 0, pattern);
	}

	void inner_insert(node_info* curr, int index, string& pattern)
	{
		if (index == (int)pattern.size())
		{
			curr->term = 1;
			return;
		}

		if (curr->child[pattern[index]] == nullptr)
		{
			curr->child[pattern[index]] = init_node();
		}

		inner_insert(curr->child[pattern[index]], index + 1, pattern);
	}

	int find(string& text)
	{
		return inner_find(root_node, text);
	}

	int inner_find(node_info* curr, string& text)
	{
		int ret = 0;
		for (int i = 0; i < (int)text.size(); i++)
		{
			while (curr != root_node && curr->child[text[i]] == nullptr)
			{
				curr = curr->fail;
			}

			if (curr->child[text[i]] != nullptr)
			{
				curr = curr->child[text[i]];
			}

			ret += curr->term;
		}
		return ret;
	}
};

//aho_corasick ac;
//ac.insert(pattern);
//ac.process();
//int count = ac.find(text);