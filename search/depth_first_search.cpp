#include <iostream>
#include <cassert>
#include <cmath>
#include <complex>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>

using namespace std;

class depth_first_search
{
public:
    int vertex_count;

    vector<bool> visited;
    vector<vector<int>> adj;

public:
    depth_first_search(int _vertex_count)
        : vertex_count(_vertex_count), visited(), adj()
    {
        visited.assign(vertex_count, false);
        adj.assign(vertex_count, vector<int>());
    }

public:
    void create_edge(int from, int to)
    {
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    int process()
    {
        int result = 0;
        for (int i = 0; i < vertex_count; i++)
        {
            if (!visited[i])
            {
                inner_process(i);
                result++;
            }
        }
        return result;
    }

    void inner_process(int curr)
    {
        visited[curr] = true;

        for (int next : adj[curr])
        {
            if (!visited[next])
            {
                inner_process(next);
            }
        }
    }
};

//depth_first_search dfs(N);
//dfs.create_edge(u, v);
//int ret_count = dfs.process();