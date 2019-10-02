#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <map>

using namespace std;

class trie
{
public:
	class node_info
	{
	public:
		bool term;

		map<char, node_info*> child;

	public:
		node_info(bool _term)
			: term(_term), child()
		{}
	};

public:
	node_info* root_node;
	vector<node_info*> node_list;

public:
	trie()
		: root_node(nullptr)
	{
		root_node = init_node();
	}

	~trie()
	{
		for (node_info* node : node_list)
		{
			delete node;
		}
	}

public:
	node_info* init_node()
	{
		node_list.push_back(new node_info(false));
		return node_list.back();
	}

	void insert(string& word)
	{
		inner_insert(root_node, 0, word);
	}

	void inner_insert(node_info* curr, int index, string& word)
	{
		if (index == word.size())
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
		return inner_find(root_node, 0, word);
	}

	bool inner_find(node_info* curr, int index, string& word)
	{
		if (index == word.size())
		{
			if (curr->term) return true;

			return false;
		}

		if (curr->child[word[index]] == nullptr)
		{
			return false;
		}

		return inner_find(curr->child[word[index]], index + 1, word);
	}
};

//trie t;
//t.insert(str);
//bool is = t.find(str);