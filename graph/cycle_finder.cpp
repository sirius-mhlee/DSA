#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <numeric>
#include <algorithm>
#include <functional>

#include <vector>

using namespace std;

class cycle_finder
{
public:
    vector<vector<int>> adj;
    vector<int> visit_state;
    vector<int> parent;

    int cycle_start;
    int cycle_end;

    vector<vector<int>> cycle_list;

public:
    cycle_finder(int vertex_count)
        : adj(), visit_state(), parent(), cycle_start(-1), cycle_end(-1), cycle_list()
    {
        adj.assign(vertex_count, vector<int>());
        visit_state.assign(vertex_count, 0);
        parent.assign(vertex_count, -1);
    }

public:
    void process()
    {
        for (int i = 0; i < (int)visit_state.size(); i++)
        {
            if (visit_state[i] == 0 && inner_process(i))
            {
                vector<int> cycle;
                for (int curr = cycle_end; curr != cycle_start; curr = parent[curr])
                {
                    visit_state[curr] = 2;
                    cycle.push_back(curr);
                }
                visit_state[cycle_start] = 2;
                cycle.push_back(cycle_start);

                reverse(cycle.begin(), cycle.end());

                cycle_list.push_back(cycle);
            }
        }
    }

    bool inner_process(int curr)
    {
        visit_state[curr] = 1;
        for (int next : adj[curr])
        {
            if (visit_state[next] == 0)
            {
                parent[next] = curr;
                if (inner_process(next))
                    return true;
            }
            else if (visit_state[next] == 1)
            {
                cycle_end = curr;
                cycle_start = next;
                return true;
            }
        }
        visit_state[curr] = 2;
        return false;
    }
};

//cycle_finder cf(N);
//cf.adj[u - 1].push_back(v - 1);
//cf.process();
//int ret = cf.cycle_list.size();