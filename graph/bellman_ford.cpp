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
class bellman_ford
{
public:
    const value_type INF = 1e9;

public:
    class edge_info
    {
    public:
        int to;

        value_type cost;

    public:
        edge_info(int _to, value_type _cost)
            : to(_to), cost(_cost)
        {}
    };

public:
    vector<vector<edge_info>> adj;
    vector<value_type> dist;

    bool negative_cycle;

public:
    bellman_ford(int vertex_count)
        : adj(), dist(), negative_cycle(false)
    {
        adj.assign(vertex_count, vector<edge_info>());
        dist.assign(vertex_count, INF);
    }

public:
    void create_edge(int from, int to, value_type cost)
    {
        adj[from].push_back(edge_info(to, cost));
    }

    void process(int start)
    {
        dist[start] = 0;

        negative_cycle = false;

        for (int k = 0; k < (int)adj.size(); k++)
        {
            for (int i = 0; i < (int)adj.size(); i++)
            {
                for (edge_info next : adj[i])
                {
                    if (dist[i] >= INF) continue;

                    if (dist[i] + next.cost < dist[next.to])
                    {
                        if (k == (int)adj.size() - 1)
                        {
                            negative_cycle = true;
                            return;
                        }

                        dist[next.to] = dist[i] + next.cost;
                    }
                }
            }
        }
    }
};

//bellman_ford<int> bf(N);
//bf.create_edge(u, v, c);
//int start = N - 2;
//bf.process(start);
//bool ret1 = bf.negative_cycle;
//int ret2 = bf.dist[N - 1];