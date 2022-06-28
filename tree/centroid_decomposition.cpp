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

class centroid_decomposition
{
public:
    vector<vector<int>> adj;
    vector<int> subtree_size;

    vector<bool> visited;

    int decompose_root;
    vector<vector<int>> decompose_adj;

public:
    centroid_decomposition(int vertex_count)
        : adj(), subtree_size(), visited(), decompose_root(-1), decompose_adj()
    {
        adj.assign(vertex_count, vector<int>());
        subtree_size.assign(vertex_count, 0);

        visited.assign(vertex_count, false);

        decompose_adj.assign(vertex_count, vector<int>());
    }

public:
    void process()
    {
        decompose_root = decompose(0);
    }

    void calc_size(int curr, int prev)
    {
        subtree_size[curr] = 1;

        for (int next : adj[curr])
        {
            if (visited[next] || next == prev) continue;

            calc_size(next, curr);
            subtree_size[curr] += subtree_size[next];
        }
    }

    int get_centroid(int curr, int prev, int size)
    {
        for (int next : adj[curr])
        {
            if (visited[next] || next == prev) continue;

            if (subtree_size[next] > size / 2)
            {
                return get_centroid(next, curr, size);
            }
        }

        return curr;
    }

    int decompose(int curr)
    {
        calc_size(curr, -1);
        int centroid = get_centroid(curr, -1, subtree_size[curr]);

        visited[centroid] = true;

        for (int next : adj[centroid])
        {
            if (visited[next]) continue;

            int next_centroid = decompose(next);

            decompose_adj[centroid].push_back(next_centroid);
            decompose_adj[next_centroid].push_back(centroid);
        }

        return centroid;
    }
};

//centroid_decomposition cd(N);
//cd.adj[u - 1].push_back(v - 1);
//cd.process();
//int ret = cd.decompose_root;
//int ret2 = cd.decompose_adj[u - 1].size();