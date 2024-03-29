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

class euler_path_circuit
{
public:
    bool directed;

    vector<vector<pair<int, int>>> adj;
    int edge_count;
    vector<bool> visited;

    vector<int> out_degree;
    vector<int> in_degree;

    vector<int> result;

public:
    euler_path_circuit(bool _directed, int vertex_count)
        : directed(_directed), adj(), edge_count(0), visited(), out_degree(), in_degree(), result()
    {
        adj.assign(vertex_count, vector<pair<int, int>>());

        out_degree.assign(vertex_count, 0);
        in_degree.assign(vertex_count, 0);
    }

public:
    void create_edge(int from, int to)
    {
        adj[from].push_back(make_pair(to, edge_count));

        out_degree[from]++;
        in_degree[to]++;
    }

    bool euler_path()
    {
        int check_count = 0;
        int start = -1;
        int end = -1;

        for (int i = 0; i < static_cast<int>(adj.size()); i++)
        {
            if (!directed)
            {
                if (out_degree[i] % 2 != 0)
                {
                    if (check_count < 2)
                    {
                        check_count++;
                        if (check_count == 1) start = i;
                        else if (check_count == 2) end = i;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                if (out_degree[i] != in_degree[i])
                {
                    if (check_count < 2)
                    {
                        check_count++;
                        if (out_degree[i] == in_degree[i] + 1) start = i;
                        else if (out_degree[i] + 1 == in_degree[i]) end = i;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }

        if (start != -1 && end != -1)
        {
            visited.assign(edge_count, false);
            inner_euler_circuit(start);
            reverse(result.begin(), result.end());
        }

        return true;
    }

    bool euler_circuit()
    {
        for (int i = 0; i < static_cast<int>(adj.size()); i++)
        {
            if (!directed)
            {
                if (out_degree[i] % 2 != 0)
                {
                    return false;
                }
            }
            else
            {
                if (out_degree[i] != in_degree[i])
                {
                    return false;
                }
            }
        }

        visited.assign(edge_count, false);
        inner_euler_circuit(0);
        reverse(result.begin(), result.end());

        return true;
    }

    void inner_euler_circuit(int curr)
    {
        while (adj[curr].size() > 0)
        {
            int next = adj[curr].back().first;
            int edge_id = adj[curr].back().second;
            adj[curr].pop_back();

            if (!visited[edge_id])
            {
                visited[edge_id] = true;
                inner_euler_circuit(next);
            }
        }

        result.push_back(curr);
    }
};

//euler_path_circuit epc(directed, N);
//epc.create_edge(u, v);
//epc.edge_count++;
//bool exist_path = epc.euler_path();
//bool exist_circuit = epc.euler_circuit();
//vector<int> ret = epc.result;