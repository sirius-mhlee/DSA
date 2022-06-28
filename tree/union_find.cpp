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

class union_find
{
public:
    vector<int> parent;
    vector<int> count;
    vector<int> rank;

public:
    union_find(int vertex_count)
        : parent(), count(), rank()
    {
        parent.assign(vertex_count, 0);
        count.assign(vertex_count, 1);
        rank.assign(vertex_count, 1);

        for (int i = 0; i < vertex_count; i++)
        {
            parent[i] = i;
        }
    }

public:
    int find(int u)
    {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);

        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);

        parent[v] = u;
        count[u] += count[v];
        if (rank[u] == rank[v]) rank[u]++;
    }

    int size(int u)
    {
        return count[find(u)];
    }
};

//union_find uf(N);
//uf.merge(u, v);
//int u_parent = uf.find(u);
//int u_size = uf.size(u);