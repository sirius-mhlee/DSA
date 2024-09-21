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

template<typename value_type>
class parallel_bin_search
{
public:
    class bin_search_info
    {
    public:
        value_type lo;
        value_type hi;

    public:
        bin_search_info(value_type _lo, value_type _hi)
            : lo(_lo), hi(_hi)
        {}
    };

public:
    vector<bin_search_info> bs_info_list;
    vector<value_type> result_list;

public:
    parallel_bin_search(int bin_search_size, value_type lo, value_type hi)
        : bs_info_list(), result_list()
    {
        bs_info_list.assign(bin_search_size, bin_search_info(lo, hi));
        result_list.assign(bin_search_size, -1);

        while (true)
        {
            bool flag = false;

            vector<vector<int>> cand_bs_info_inv(hi, vector<int>());

            for (int i = 0; i < bin_search_size; i++)
            {
                if (bs_info_list[i].hi - bs_info_list[i].lo >= 2)
                {
                    flag = true;

                    value_type mid = (bs_info_list[i].lo + bs_info_list[i].hi) / 2;
                    cand_bs_info_inv[mid].push_back(i);
                }
            }

            if (!flag) break;

            for (value_type i = 0; i < hi; i++)
            {
                func(i);

                for (int idx : cand_bs_info_inv[i])
                {
                    if (check(idx))
                    {
                        bs_info_list[idx].hi = i;
                        result_list[idx] = i + 1;
                    }
                    else
                    {
                        bs_info_list[idx].lo = i;
                    }
                }
            }
        }
    }

public:
    void func(value_type val)
    {

    }

    bool check(int idx)
    {
        if (idx)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

//parallel_bin_search<long long> pbs(N, lo - 1, hi + 1);
//long long ret = pbs.result_list[i];