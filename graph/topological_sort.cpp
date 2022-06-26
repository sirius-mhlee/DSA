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

class topological_sort
{
public:
    vector<vector<int>> adj;

    vector<int> in_degree;

    bool cycle;
    vector<int> result;

public:
    topological_sort(int vertex_count)
        : adj(), in_degree(), cycle(false), result()
    {
        adj.assign(vertex_count, vector<int>());

        in_degree.assign(vertex_count, 0);
    }

public:
    void create_edge(int from, int to)
    {
        adj[from].push_back(to);

        in_degree[to]++;
    }

    void process()
    {
        queue<int> q;

        for (int i = 0; i < (int)in_degree.size(); i++)
        {
            if (in_degree[i] == 0)
            {
                q.push(i);
            }
        }

        for (int i = 0; i < (int)adj.size(); i++)
        {
            if (q.empty())
            {
                cycle = true;
                break;
            }

            int curr = q.front();
            q.pop();

            result.push_back(curr);

            for (int next : adj[curr])
            {
                in_degree[next]--;
                if (in_degree[next] == 0)
                {
                    q.push(next);
                }
            }
        }
    }
};

//topological_sort ts(V);
//ts.create_edge(u - 1, v - 1);
//ts.process();
//bool ret1 = ts.cycle;
//int ret2 = ts.result[k];