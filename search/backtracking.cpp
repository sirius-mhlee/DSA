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

using namespace std;

class backtracking
{
public:
    int max_state_value;
    int depth_limit;

    vector<int> curr_state;
    vector<vector<int>> state_list;

public:
    backtracking(int _max_state_value, int _depth_limit)
        : max_state_value(_max_state_value), depth_limit(_depth_limit), curr_state(), state_list()
    {
        curr_state.assign(depth_limit, 0);
    }

public:
    void process(int prev_state_value, int curr_depth)
    {
        if (curr_depth == depth_limit)
        {
            state_list.push_back(curr_state);
            return;
        }

        for (int next_state_value = prev_state_value + 1; next_state_value < max_state_value; next_state_value++)
        {
            curr_state[curr_depth] = next_state_value;
            process(next_state_value, curr_depth + 1);
        }
    }
};

//backtracking bt(N, M);
//bt.process(-1, 0);
//vector<vector<int>> state_list = bt.state_list;