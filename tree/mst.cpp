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
class mst
{
public:
    class edge_info
    {
    public:
        int from;
        int to;

        value_type cost;

    public:
        edge_info(int _from, int _to, value_type _cost)
            : from(_from), to(_to), cost(_cost)
        {}
    };

public:
    int vertex_count;

    union_find uf;
    vector<edge_info> edge_list;

    value_type cost_result;

public:
    mst(int _vertex_count)
        : vertex_count(_vertex_count), uf(_vertex_count), edge_list(), cost_result(0)
    {}

public:
    void create_edge(int from, int to, value_type cost)
    {
        edge_list.push_back(edge_info(from, to, cost));
    }

    void process()
    {
        sort(edge_list.begin(), edge_list.end(), [](const edge_info& l, const edge_info& r)
        {
            return l.cost < r.cost;
        });

        int cnt = 0;

        for (edge_info edge : edge_list)
        {
            int from_parent = uf.find(edge.from);
            int to_parent = uf.find(edge.to);

            if (from_parent == to_parent) continue;

            uf.merge(from_parent, to_parent);

            cost_result += edge.cost;
            cnt++;

            if (cnt == vertex_count - 1) break;
        }
    }
};

//mst<int> m(N);
//m.create_edge(u, v, c);
//m.process();
//int ret = m.cost_result;