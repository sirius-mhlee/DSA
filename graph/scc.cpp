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

class scc
{
public:
	vector<vector<int>> adj;

	vector<int> vertex_scc_id;
	vector<vector<int>> scc_group_vertex;

	int dfs_visit_cnt;
	vector<int> dfs_num;
	vector<bool> finished;

	vector<int> s;

	vector<vector<int>> scc_adj;
	vector<int> scc_in_degree;

public:
	scc(int vertex_count)
		: adj(), vertex_scc_id(), scc_group_vertex(), dfs_visit_cnt(0), dfs_num(), finished(), s(), scc_adj(), scc_in_degree()
	{
		adj.assign(vertex_count, vector<int>());

		vertex_scc_id.assign(vertex_count, -1);

		dfs_num.assign(vertex_count, 0);
		finished.assign(vertex_count, false);
	}

public:
	void compute_scc()
	{
		for (int i = 0; i < (int)finished.size(); i++)
		{
			if (!finished[i])
				inner_compute_scc(i);
		}

		scc_adj.assign(scc_group_vertex.size(), vector<int>());
		scc_in_degree.assign(scc_group_vertex.size(), 0);

		for (int i = 0; i < (int)adj.size(); i++)
		{
			for (int j : adj[i])
			{
				if (vertex_scc_id[i] != vertex_scc_id[j])
				{
					scc_adj[vertex_scc_id[i]].push_back(vertex_scc_id[j]);
					scc_in_degree[vertex_scc_id[j]]++;
				}
			}
		}
	}

	int inner_compute_scc(int curr)
	{
		dfs_visit_cnt++;
		dfs_num[curr] = dfs_visit_cnt;
		s.push_back(curr);

		int ret = dfs_num[curr];
		for (int next : adj[curr])
		{
			if (dfs_num[next] == 0)
				ret = min(ret, inner_compute_scc(next));
			else if (!finished[next])
				ret = min(ret, dfs_num[next]);
		}

		if (ret == dfs_num[curr])
		{
			vector<int> scc_curr;
			while (true)
			{
				int t = s.back();
				s.pop_back();

				vertex_scc_id[t] = scc_group_vertex.size();
				scc_curr.push_back(t);
				finished[t] = true;

				if (t == curr) break;
			}
			scc_group_vertex.push_back(scc_curr);
		}

		return ret;
	}
};

//scc s(V);
//s.adj[u - 1].push_back(v - 1);
//s.compute_scc();
//int ret1 = s.scc_group_vertex.size();
//int ret2 = s.scc_adj[s.vertex_scc_id[u]].size();