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

class bipartite_matching
{
public:
	vector<vector<int>> adj;

	vector<bool> visited;
	vector<int> match;

	int match_count;

public:
	bipartite_matching(int left_vertex_count, int right_vertex_count)
		: adj(), visited(), match(), match_count(0)
	{
		adj.assign(left_vertex_count, vector<int>());

		visited.assign(right_vertex_count, false);
		match.assign(right_vertex_count, -1);
	}

public:
	void process()
	{
		for (int i = 0; i < adj.size(); i++)
		{
			fill(visited.begin(), visited.end(), false);

			if (dfs(i)) match_count++;
		}
	}

	bool dfs(int here)
	{
		for (int there : adj[here])
		{
			if (visited[there]) continue;

			visited[there] = true;
			if (match[there] == -1 || dfs(match[there]))
			{
				match[there] = here;
				return true;
			}
		}

		return false;
	}
};

//bipartite_matching bm(N, M);
//bm.adj[u - 1].push_back(v - 1);
//bm.process();
//int ret = bm.match_count;