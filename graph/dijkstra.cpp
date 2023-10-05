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
#include <deque>
#include <queue>

using namespace std;

template<typename value_type>
class dijkstra
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

    public:
        bool operator<(const edge_info& o) const
        {
            return cost > o.cost;
        }
    };

public:
    int vertex_count;

    vector<vector<edge_info>> adj;
    vector<value_type> dist;
    vector<int> prev;

public:
    dijkstra(int _vertex_count)
        : vertex_count(_vertex_count), adj(), dist(), prev()
    {
        adj.assign(vertex_count, vector<edge_info>());
        dist.assign(vertex_count, INF);
        prev.assign(vertex_count, -1);
    }

public:
    void create_edge(int from, int to, value_type cost)
    {
        adj[from].push_back(edge_info(to, cost));
    }

    void process(int start)
    {
        for (int i = 0; i < vertex_count; i++)
        {
            sort(adj[i].begin(), adj[i].end(), [](const edge_info& l, const edge_info& r)
            {
                return l.cost < r.cost;
            });
        }
        
        dist.assign(vertex_count, INF);
        prev.assign(vertex_count, -1);

        priority_queue<edge_info> pq;
        dist[start] = 0;
        pq.push(edge_info(start, 0));

        while (!pq.empty())
        {
            value_type curr_dist = pq.top().cost;
            int curr_node = pq.top().to;
            pq.pop();

            if (curr_dist > dist[curr_node]) continue;

            for (edge_info next : adj[curr_node])
            {
                value_type next_dist = curr_dist + next.cost;
                int next_node = next.to;

                if (next_dist < dist[next_node])
                {
                    prev[next_node] = curr_node;

                    dist[next_node] = next_dist;
                    pq.push(edge_info(next_node, next_dist));
                }
            }
        }
    }

    deque<int> get_path(int end)
    {
        deque<int> path;

        int curr_node = end;
        while (prev[curr_node] != -1)
        {
            path.push_front(curr_node);
            curr_node = prev[curr_node];
        }
        path.push_front(curr_node);

        return path;
    }
};

//dijkstra<int> ds(N);
//ds.create_edge(u, v, c);
//int start = N - 2;
//int end = N - 1;
//ds.process(start);
//int ret = ds.dist[end];
//deque<int> shortest_path = ds.get_path(end);