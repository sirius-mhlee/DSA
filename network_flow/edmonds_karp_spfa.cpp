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

template<typename value_type>
class edmonds_karp_spfa
{
public:
    const value_type INF = 1e9;

public:
    class edge_info
    {
    public:
        int to;

        value_type capa;
        value_type cost;
        value_type flow;

        edge_info* rev;

    public:
        edge_info(int _to, value_type _capa, value_type _cost)
            : to(_to), capa(_capa), cost(_cost), flow(0), rev(nullptr)
        {}

    public:
        value_type get_remain()
        {
            return (capa - flow);
        }

        void set_flow(value_type value)
        {
            flow += value;
            rev->flow -= value;
        }
    };

public:
    vector<edge_info*> edge_list;

    vector<vector<edge_info*>> adj;

    value_type cost_result;
    value_type flow_result;

public:
    edmonds_karp_spfa(int vertex_count)
        : edge_list(), adj(), cost_result(0), flow_result(0)
    {
        adj.assign(vertex_count, vector<edge_info*>());
    }

    ~edmonds_karp_spfa()
    {
        for (edge_info* e : edge_list)
        {
            delete e;
        }
    }

public:
    void create_edge(int from, int to, value_type capa, value_type cost)
    {
        edge_info* edge1 = new edge_info(to, capa, cost);
        edge_info* edge2 = new edge_info(from, 0, -cost);

        edge1->rev = edge2;
        edge2->rev = edge1;

        adj[from].push_back(edge1);
        adj[to].push_back(edge2);

        edge_list.push_back(edge1);
        edge_list.push_back(edge2);
    }

    void process(int start, int end)
    {
        while (true)
        {
            vector<int> prev(adj.size(), -1);
            vector<edge_info*> path(adj.size(), nullptr);

            vector<value_type> dist(adj.size(), INF);
            vector<bool> in_q(adj.size(), false);

            queue<int> q;

            dist[start] = 0;
            in_q[start] = true;
            q.push(start);

            while (!q.empty())
            {
                int curr = q.front();
                q.pop();

                in_q[curr] = false;

                for (edge_info* e : adj[curr])
                {
                    int next = e->to;
                    if (e->get_remain() > 0 && dist[next] > dist[curr] + e->cost)
                    {
                        prev[next] = curr;
                        path[next] = e;

                        dist[next] = dist[curr] + e->cost;

                        if (!in_q[next])
                        {
                            in_q[next] = true;
                            q.push(next);
                        }
                    }
                }
            }

            if (prev[end] == -1) break;

            value_type min_flow = INF;
            for (int i = end; i != start; i = prev[i])
            {
                min_flow = min(min_flow, path[i]->get_remain());
            }

            for (int i = end; i != start; i = prev[i])
            {
                cost_result += (min_flow * path[i]->cost);
                path[i]->set_flow(min_flow);
            }

            flow_result += min_flow;
        }
    }
};

//edmonds_karp_spfa<int> eks(N);
//eks.create_edge(u, v, capa, cost);
//int start = N - 2;
//int end = N - 1;
//eks.process(start, end);
//int ret1 = eks.flow_result;
//int ret2 = eks.cost_result;