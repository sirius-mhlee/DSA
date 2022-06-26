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

class lca
{
public:
    int logN;

    vector<vector<int>> adj;
    vector<vector<int>> parent;
    vector<int> depth;

public:
    lca(int vertex_count)
        : logN(0), adj(), parent(), depth()
    {
        logN = log2(vertex_count) + 1;

        adj.assign(vertex_count, vector<int>());
        parent.assign(vertex_count, vector<int>(logN, -1));
        depth.assign(vertex_count, -1);
    }

public:
    void process(int root)
    {
        depth[root] = 0;
        make_dfs_tree(root);
        update_parent();
    }

    void make_dfs_tree(int curr)
    {
        for (int next : adj[curr])
        {
            if (depth[next] != -1) continue;

            parent[next][0] = curr;
            depth[next] = depth[curr] + 1;

            make_dfs_tree(next);
        }
    }

    void update_parent()
    {
        for (int j = 0; j < logN - 1; j++)
        {
            for (int i = 0; i < (int)parent.size(); i++)
            {
                if (parent[i][j] != -1)
                {
                    parent[i][j + 1] = parent[parent[i][j]][j];
                }
            }
        }
    }

    int get_lca(int u, int v)
    {
        if (depth[u] < depth[v]) swap(u, v);

        for (int i = logN - 1; i >= 0; i--)
        {
            if (parent[u][i] != -1)
            {
                if (depth[u] - depth[v] >= (1 << i))
                {
                    u = parent[u][i];
                }
            }
        }

        if (u != v)
        {
            for (int i = logN - 1; i >= 0; i--)
            {
                if (parent[u][i] != -1 && parent[v][i] != -1)
                {
                    if (parent[u][i] != parent[v][i])
                    {
                        u = parent[u][i];
                        v = parent[v][i];
                    }
                }
            }

            u = parent[u][0];
        }

        return u;
    }
};

//lca l(N);
//l.adj[u - 1].push_back(v - 1);
//l.process(root);
//int ret = l.get_lca(u - 1, v - 1);