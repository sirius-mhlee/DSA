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

public:
    union_find(int vertex_count)
        : parent()
    {
        parent.assign(vertex_count, 0);

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
        parent[find(v)] = find(u);
    }
};

//union_find uf(N);
//uf.merge(u, v);
//int u_parent = uf.find(u);