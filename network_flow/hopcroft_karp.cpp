#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

#include <vector>
#include <queue>

using namespace std;

class hopcroft_karp
{
public:
    vector<vector<int>> adj;
    vector<int> level;

    vector<bool> visited;
    vector<int> match;

    int match_count;

public:
    hopcroft_karp(int left_vertex_count, int right_vertex_count)
        : adj(), level(), visited(), match(), match_count(0)
    {
        adj.assign(left_vertex_count, vector<int>());
        level.assign(left_vertex_count, -1);
        visited.assign(left_vertex_count, false);

        match.assign(right_vertex_count, -1);
    }

public:
    void process()
    {
        while (true)
        {
            hopcroft_karp_bfs();

            int count = 0;
            for (int i = 0; i < (int)adj.size(); i++)
            {
                if (!visited[i] && hopcroft_karp_dfs(i))
                {
                    count++;
                }
            }

            if (count == 0) break;

            match_count += count;
        }
    }

    void hopcroft_karp_bfs()
    {
        fill(level.begin(), level.end(), -1);

        queue<int> q;
        for (int i = 0; i < (int)adj.size(); i++)
        {
            if (!visited[i])
            {
                level[i] = 0;
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int next : adj[curr])
            {
                if (match[next] != -1 && level[match[next]] == -1)
                {
                    level[match[next]] = level[curr] + 1;
                    q.push(match[next]);
                }
            }
        }
    }

    bool hopcroft_karp_dfs(int curr)
    {
        for (int next : adj[curr])
        {
            if (match[next] == -1 || (level[match[next]] == level[curr] + 1 && hopcroft_karp_dfs(match[next])))
            {
                visited[curr] = true;
                match[next] = curr;

                return true;
            }
        }

        return false;
    }
};

//hopcroft_karp hk(N, M);
//hk.adj[u - 1].push_back(v - 1);
//hk.process();
//int ret = hk.match_count;