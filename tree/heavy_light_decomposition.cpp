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
class heavy_light_decomposition
{
public:
    class edge_info
    {
    public:
        int to;

        value_type value;
        int id;

    public:
        edge_info(int _to, value_type _value, int _id)
            : to(_to), value(_value), id(_id)
        {}
    };

public:
    vector<vector<edge_info>> adj;
    vector<int> subtree_size;

    vector<int> parent;
    vector<int> depth;

    vector<int> chain_next;
    vector<int> chain_id;
    vector<int> chain_head;
    int chain_count;

    vector<int> to_datalist_idx;
    int datalist_idx_count;

public:
    heavy_light_decomposition(int vertex_count)
        : adj(), subtree_size(), parent(), depth(), chain_next(), chain_id(), chain_head(), chain_count(0), to_datalist_idx(), datalist_idx_count(0)
    {
        adj.assign(vertex_count, vector<edge_info>());
        subtree_size.assign(vertex_count, 0);

        parent.assign(vertex_count, 0);
        depth.assign(vertex_count, 0);

        chain_next.assign(vertex_count, -1);
        chain_id.assign(vertex_count, 0);
        chain_head.assign(vertex_count, -1);

        to_datalist_idx.assign(vertex_count, 0);
    }

public:
    void create_edge(int from, int to, value_type value, int id)
    {
        adj[from].push_back(edge_info(to, value, id));
        adj[to].push_back(edge_info(from, value, id));
    }

    void process(int root)
    {
        dfs(root, -1, 0);
        decompose(root, -1);
    }

    void dfs(int curr, int prev, int curr_depth)
    {
        subtree_size[curr] = 1;
        parent[curr] = prev;
        depth[curr] = curr_depth;

        for (edge_info e : adj[curr])
        {
            if (e.to == prev) continue;

            dfs(e.to, curr, curr_depth + 1);

            subtree_size[curr] += subtree_size[e.to];
            if (chain_next[curr] == -1 || subtree_size[e.to] > subtree_size[chain_next[curr]])
            {
                chain_next[curr] = e.to;
            }
        }
    }

    void decompose(int curr, int prev)
    {
        to_datalist_idx[curr] = datalist_idx_count;
        datalist_idx_count++;

        chain_id[curr] = chain_count;
        if (chain_head[chain_count] == -1) chain_head[chain_count] = curr;

        if (chain_next[curr] != -1) decompose(chain_next[curr], curr);

        for (edge_info e : adj[curr])
        {
            if (e.to == prev || e.to == chain_next[curr]) continue;

            chain_count++;
            decompose(e.to, curr);
        }
    }

    value_type query(int u, int v)
    {
        value_type ret = 0;

        while (chain_id[u] != chain_id[v])
        {
            if (depth[chain_head[chain_id[u]]] < depth[chain_head[chain_id[v]]]) swap(u, v);
            ret = max(ret, seg.query(to_datalist_idx[chain_head[chain_id[u]]], to_datalist_idx[u]));

            u = parent[chain_head[chain_id[u]]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        ret = max(ret, seg.query(to_datalist_idx[u] + 1, to_datalist_idx[v]));

        return ret;
    }
};

//heavy_light_decomposition<int> hld(N);
//hld.create_edge(u - 1, v - 1, value, id);
//hld.process(root);
//int ret = hld.query(u - 1, v - 1);