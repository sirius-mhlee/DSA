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
class dinic
{
public:
    const value_type INF = 1e9;

public:
    class edge_info
    {
    public:
        int to;

        value_type capa;
        value_type flow;

        edge_info* rev;

    public:
        edge_info(int _to, value_type _capa)
            : to(_to), capa(_capa), flow(0), rev(nullptr)
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
    vector<int> level;
    vector<int> search_id;

    value_type flow_result;

public:
    dinic(int vertex_count)
        : edge_list(), adj(), level(), search_id(), flow_result(0)
    {
        adj.assign(vertex_count, vector<edge_info*>());
        level.assign(vertex_count, -1);
        search_id.assign(vertex_count, 0);
    }

    ~dinic()
    {
        for (edge_info* e : edge_list)
        {
            delete e;
        }
    }

public:
    void create_edge(int from, int to, value_type capa)
    {
        edge_info* edge1 = new edge_info(to, capa);
        edge_info* edge2 = new edge_info(from, 0);

        edge1->rev = edge2;
        edge2->rev = edge1;

        adj[from].push_back(edge1);
        adj[to].push_back(edge2);

        edge_list.push_back(edge1);
        edge_list.push_back(edge2);
    }

    void process(int start, int end)
    {
        while (dinic_bfs(start, end))
        {
            fill(search_id.begin(), search_id.end(), 0);

            while (true)
            {
                value_type min_flow = dinic_dfs(start, end, INF);
                if (min_flow == 0) break;

                flow_result += min_flow;
            }
        }
    }

    bool dinic_bfs(int start, int end)
    {
        fill(level.begin(), level.end(), -1);
        level[start] = 0;

        queue<int> q;
        q.push(start);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (edge_info* e : adj[curr])
            {
                int next = e->to;
                if (e->get_remain() > 0 && level[next] == -1)
                {
                    level[next] = level[curr] + 1;
                    q.push(next);
                }
            }
        }

        if (level[end] == -1) return false;

        return true;
    }

    value_type dinic_dfs(int curr, int dest, value_type flow)
    {
        if (curr == dest) return flow;

        for (int& id = search_id[curr]; id < (int)adj[curr].size(); id++)
        {
            edge_info* e = adj[curr][id];

            int next = e->to;
            if (e->get_remain() > 0 && level[next] == level[curr] + 1)
            {
                value_type min_flow = dinic_dfs(next, dest, min(flow, e->get_remain()));
                if (min_flow > 0)
                {
                    e->set_flow(min_flow);
                    return min_flow;
                }
            }
        }

        return 0;
    }
};

//dinic<int> dn(N);
//dn.create_edge(u, v, c);
//int start = N - 2;
//int end = N - 1;
//dn.process(start, end);
//int ret = dn.flow_result;