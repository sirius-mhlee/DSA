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
class floyd_warshall
{
public:
    const value_type INF = 1e9;

public:
    vector<vector<value_type>> dist;

public:
    floyd_warshall(int vertex_count)
        : dist()
    {
        dist.assign(vertex_count, vector<value_type>(vertex_count, INF));
    }

public:
    void create_edge(int from, int to, value_type cost)
    {
        dist[from][to] = cost;
    }

    void process()
    {
        for (int k = 0; k < (int)dist.size(); k++)
        {
            for (int i = 0; i < (int)dist.size(); i++)
            {
                for (int j = 0; j < (int)dist.size(); j++)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};

//floyd_warshall<int> fw(N);
//fw.create_edge(u, v, c);
//fw.process();
//int ret = fw.dist[a][b];