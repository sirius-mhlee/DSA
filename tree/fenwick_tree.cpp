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
class fenwick_tree
{
public:
    vector<value_type> tree;

public:
    fenwick_tree(int data_count)
        : tree()
    {
        tree.assign(data_count + 1, 0);
    }

public:
    void update(int idx, value_type diff)
    {
        idx++;

        while (idx < (int)tree.size())
        {
            tree[idx] += diff;
            idx += (idx & -idx);
        }
    }

    value_type query(int idx)
    {
        idx++;

        value_type ret = 0;
        while (idx > 0)
        {
            ret += tree[idx];
            idx -= (idx & -idx);
        }
        return ret;
    }
};

//fenwick_tree<long long> fen(N);
//fen.update(i, diff);
//long long ret = fen.query(j);