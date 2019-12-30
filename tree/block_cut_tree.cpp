#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class block_cut_tree
{
public:
	class bcc_node_info
	{
	public:
		bool cut_vertex;
		bool cut_edge;

		vector<int> adj_node;

	public:
		bcc_node_info(bool _cut_vertex, bool _cut_edge)
			: cut_vertex(_cut_vertex), cut_edge(_cut_edge)
		{}
	};

	class edge_info
	{
	public:
		int from;
		int to;

	public:
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
	unordered_map<int, unordered_map<int, int>> edge_to_id;

	vector<int> vertex_bcc_id;
	vector<int> edge_bcc_id;
	vector<vector<edge_info>> bcc_group_edge;
	vector<bcc_node_info> bcc_node_list;

	int dfs_visit_cnt;
	vector<int> dfs_num;

	vector<edge_info> s;

	unordered_set<int> cut_vertex_set;

public:
	block_cut_tree(int vertex_count, int edge_count)
		: edge_to_id(), vertex_bcc_id(), edge_bcc_id(), bcc_group_edge(), bcc_node_list(), dfs_visit_cnt(0), dfs_num(), s(), cut_vertex_set()
	{
		vertex_bcc_id.assign(vertex_count, 0);
		edge_bcc_id.assign(edge_count, 0);

		dfs_num.assign(vertex_count, 0);
	}

public:
	void process()
	{
		for (int i = 0; i < (int)dfs_num.size(); i++)
		{
			if (edge_to_id[i].size() == 1) cut_vertex_set.insert(i);

			if (dfs_num[i] == 0)
			{
				compute_bcc(-1, i);
			}
		}

		for (int v : cut_vertex_set)
		{
			bcc_node_info bcc_node(true, false);
			for (pair<int, int> e : edge_to_id[v])
			{
				int bcc_id = edge_bcc_id[e.second];
				bcc_node.adj_node.push_back(bcc_id);
				bcc_node_list[bcc_id].adj_node.push_back(bcc_node_list.size());
			}
			vertex_bcc_id[v] = bcc_node_list.size();
			bcc_node_list.push_back(bcc_node);
		}
	}

	int compute_bcc(int prev, int curr)
	{
		dfs_visit_cnt++;
		dfs_num[curr] = dfs_visit_cnt;

		int ret = dfs_num[curr];
		for (pair<int, int> e : edge_to_id[curr])
		{
			int next = e.first;
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
				int ret_next = compute_bcc(curr, next);
				ret = min(ret, ret_next);

				if (ret_next >= dfs_num[curr])
				{
					vector<edge_info> bcc_curr;
					while (!s.empty())
					{
						edge_info t = s.back();
						s.pop_back();

						vertex_bcc_id[t.from] = bcc_group_edge.size();
						vertex_bcc_id[t.to] = bcc_group_edge.size();
						edge_bcc_id[edge_to_id[t.from][t.to]] = bcc_group_edge.size();

						bcc_curr.push_back(t);

						if (t == curr_edge) break;
					}
					cut_vertex_set.insert(curr);

					bcc_node_info bcc_node(false, false);
					if (bcc_curr.size() == 1) bcc_node.cut_edge = true;

					bcc_group_edge.push_back(bcc_curr);
					bcc_node_list.push_back(bcc_node);
				}
			}
		}

		return ret;
	}
};

//block_cut_tree bct(V, E);
//bct.edge_to_id[u - 1][v - 1] = i;
//bct.process();
//int ret = bct.bcc_node_list.size();