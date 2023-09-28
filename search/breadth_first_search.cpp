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
#include <queue>

using namespace std;

class breadth_first_search
{
public:
    vector<bool> visited;
    vector<vector<int>> adj;

public:
    breadth_first_search(int vertex_count)
        : visited(), adj()
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

    int process(int start, int end)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(start, 0));
        visited[start] = true;
        while (!q.empty())
        {
            int curr = q.front().first;
            int curr_depth = q.front().second;
            q.pop();

            if (curr == end)
            {
                return curr_depth;
            }

            for (int next : adj[curr])
            {
                if (!visited[next])
                {
                    q.push(make_pair(next, curr_depth + 1));
                    visited[next] = true;
                }
            }
        }
        return -1;
    }
};

//breadth_first_search bfs(N);
//bfs.create_edge(u, v);
//int ret_depth = bfs.process(start, end);