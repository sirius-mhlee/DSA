#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <set>

using namespace std;

class bcc
{
public:
	class edge_info
	{
	public:
		int from;
		int to;

	public:
		edge_info()
			: from(-1), to(-1)
		{}

		edge_info(int _from, int _to)
			: from(_from), to(_to)
		{}

	public:
		bool operator <(const edge_info& o) const
		{
			if (from < o.from) return true;
			else if (o.from < from) return false;
			else if (to < o.to) return true;
			return false;
		}

		bool operator ==(const edge_info& o) const
		{
			if (from == o.from && to == o.to) return true;
			return false;
		}
	};

public:
	vector<vector<int>> adj;

	vector<set<int>> vertex_bcc_id;
	vector<vector<edge_info>> bcc_group_edge;

	int dfs_visit_cnt;
	vector<int> dfs_num;

	vector<edge_info> s;

	vector<int> cut_vertex;
	set<edge_info> cut_edge;

public:
	bcc(int vertex_count)
		: adj(), vertex_bcc_id(), bcc_group_edge(), dfs_visit_cnt(0), dfs_num(), s(), cut_vertex(), cut_edge()
	{
		adj.assign(vertex_count, vector<int>());

		vertex_bcc_id.assign(vertex_count, set<int>());

		dfs_num.assign(vertex_count, 0);
	}

public:
	void compute_bcc()
	{
		for (int i = 0; i < (int)dfs_num.size(); i++)
		{
			if (dfs_num[i] == 0)
				inner_compute_bcc(-1, i);
		}

		for (int i = 0; i < (int)dfs_num.size(); i++)
		{
			if (vertex_bcc_id[i].size() > 1) cut_vertex.push_back(i);
		}
	}

	int inner_compute_bcc(int prev, int curr)
	{
		dfs_visit_cnt++;
		dfs_num[curr] = dfs_visit_cnt;

		int ret = dfs_num[curr];
		for (int next : adj[curr])
		{
			if (next == prev) continue;

			edge_info curr_edge(curr, next);

			if (dfs_num[curr] > dfs_num[next])
				s.push_back(curr_edge);

			if (dfs_num[next] > 0)
			{
				ret = min(ret, dfs_num[next]);
			}
			else
			{
				int ret_next = inner_compute_bcc(curr, next);
				ret = min(ret, ret_next);

				if (ret_next >= dfs_num[curr])
				{
					if (ret_next > dfs_num[curr])
					{
						edge_info e(curr, next);
						if (next < curr) swap(e.from, e.to);

						cut_edge.insert(e);
					}

					vector<edge_info> bcc_curr;
					while (!s.empty())
					{
						edge_info e = s.back();
						s.pop_back();

						vertex_bcc_id[e.from].insert(bcc_group_edge.size());
						vertex_bcc_id[e.to].insert(bcc_group_edge.size());
						bcc_curr.push_back(e);

						if (e == curr_edge) break;
					}
					bcc_group_edge.push_back(bcc_curr);
				}
			}
		}

		return ret;
	}
};

//bcc b(V);
//b.adj[u - 1].push_back(v - 1);
//b.compute_bcc();
//int ret = b.cut_edge.size();