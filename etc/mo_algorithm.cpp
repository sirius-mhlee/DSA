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
class mo_algorithm
{
public:
    class query_info
    {
    public:
        int left;
        int right;

        int idx;

    public:
        query_info(int _left, int _right, int _idx)
            : left(_left), right(_right), idx(_idx)
        {}
    };

public:
    vector<value_type> data_list;

    int query_unit_size;
    vector<query_info> query_list;

    value_type query_result;
    vector<value_type> query_result_list;

public:
    mo_algorithm(int data_count)
        : data_list(), query_unit_size(0), query_list(), query_result(0), query_result_list()
    {
        data_list.assign(data_count, 0);

        query_unit_size = sqrt(data_count);
    }

public:
    void add_query(int left, int right, int idx)
    {
        query_list.push_back(query_info(left, right, idx));
    }

    void include_query(value_type val)
    {
        query_result += val;
    }

    void exclude_query(value_type val)
    {
        query_result -= val;
    }

    void process()
    {
        query_result = 0;
        query_result_list.assign(query_list.size(), 0);

        sort(query_list.begin(), query_list.end(), [&](const query_info& l, const query_info& r)
        {
            int lidx = l.left / query_unit_size;
            int ridx = r.left / query_unit_size;

            if (lidx == ridx)
            {
                return l.right < r.right;
            }
            return lidx < ridx;
        });

        int left = 0;
        int right = 0;
        include_query(data_list[0]);

        for (query_info curr : query_list)
        {
            while (left - 1 >= curr.left)
            {
                include_query(data_list[left - 1]);
                left--;
            }

            while (right + 1 <= curr.right)
            {
                include_query(data_list[right + 1]);
                right++;
            }

            while (left < curr.left)
            {
                exclude_query(data_list[left]);
                left++;
            }

            while (right > curr.right)
            {
                exclude_query(data_list[right]);
                right--;
            }

            query_result_list[curr.idx] = query_result;
        }
    }
};

//mo_algorithm<int> ma(N);
//ma.data_list[i] = val;
//ma.add_query(left, right, idx);
//ma.process();
//vector<int> ret = ma.query_result_list;