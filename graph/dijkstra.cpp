#include <iostream>
#include <cmath>
#include <complex>
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
    };

public:
    int vertex_count;

    vector<vector<edge_info>> adj;
    vector<value_type> dist;
    deque<int> path;

public:
    dijkstra(int _vertex_count)
        : vertex_count(_vertex_count), adj(), dist(), path()
    {
        adj.assign(vertex_count, vector<edge_info>());
        dist.assign(vertex_count, INF);
    }

public:
    void create_edge(int from, int to, value_type cost)
    {
        adj[from].push_back(edge_info(to, cost));
    }

    void process(int start, int end)
    {
        dist.assign(vertex_count, INF);
        path.clear();

        vector<int> prev(vertex_count, -1);

        priority_queue<pair<value_type, int>, vector<pair<value_type, int>>, greater<pair<value_type, int>>> pq;
        dist[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty())
        {
            value_type curr_dist = pq.top().first;
            int curr_node = pq.top().second;
            pq.pop();

            if (curr_dist > dist[curr_node]) continue;

            for (edge_info next : adj[curr_node])
            {
                int next_dist = curr_dist + next.cost;
                int next_node = next.to;

                if (next_dist < dist[next_node])
                {
                    prev[next_node] = curr_node;

                    dist[next_node] = next_dist;
                    pq.push(make_pair(next_dist, next_node));
                }
            }
        }

        int curr_node = end;
        while (prev[curr_node] != -1)
        {
            path.push_front(curr_node);
            curr_node = prev[curr_node];
        }
        path.push_front(start);
    }
};

//dijkstra<int> ds(N);
//ds.create_edge(u, v, c);
//int start = N - 2;
//int end = N - 1;
//ds.process(start, end);
//int ret = ds.dist[end];
//deque<int> shortest_path = ds.path;