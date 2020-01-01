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
		bool term;

		map<char, node_info*> child;
		node_info* fail;

	public:
		node_info()
			: term(false), child(), fail(nullptr)
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
				next->term |= next_fail->term;
				q.push(next);
			}
		}
	}

	void insert(string& word)
	{
		inner_insert(root_node, 0, word);
	}

	void inner_insert(node_info* curr, int index, string& word)
	{
		if (index == (int)word.size())
		{
			curr->term = true;
			return;
		}

		if (curr->child[word[index]] == nullptr)
		{
			curr->child[word[index]] = init_node();
		}

		inner_insert(curr->child[word[index]], index + 1, word);
	}

	bool find(string& word)
	{
		return inner_find(root_node, word);
	}

	bool inner_find(node_info* curr, string& word)
	{
		for (int i = 0; i < (int)word.size(); i++)
		{
			while (curr != root_node && curr->child[word[i]] == nullptr)
			{
				curr = curr->fail;
			}

			if (curr->child[word[i]] != nullptr)
			{
				curr = curr->child[word[i]];
			}

			if (curr->term)
			{
				return true;
			}
		}

		return false;
	}
};

//aho_corasick ac;
//ac.insert(str);
//ac.process();
//bool is = ac.find(str);