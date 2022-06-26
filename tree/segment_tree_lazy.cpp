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
class segment_tree_lazy
{
public:
    class lazy_info
    {
    public:
        bool flag;

        value_type val;

    public:
        lazy_info(bool _flag, value_type _val)
            : flag(_flag), val(_val)
        {}
    };

public:
    int data_count;
    vector<value_type> data_list;

    vector<lazy_info> lazy;
    vector<value_type> tree;

public:
    segment_tree_lazy(int _data_count)
        : data_count(_data_count), data_list(), lazy(), tree()
    {
        data_list.assign(data_count, 0);

        int height = (int)ceil(log2(data_count));
        int tree_size = (1 << (height + 1));
        lazy.assign(tree_size, lazy_info(false, 0));
        tree.assign(tree_size, 0);
    }

public:
    void init()
    {
        inner_init(1, 0, data_count - 1);
    }

    value_type inner_init(int node, int start, int end)
    {
        if (start == end)
        {
            return tree[node] = data_list[start];
        }
        else
        {
            int mid = (start + end) / 2;
            return tree[node] = inner_init(node * 2, start, mid) + inner_init(node * 2 + 1, mid + 1, end);
        }
    }

    void propagate(int node, int start, int end)
    {
        if (lazy[node].flag)
        {
            if (start != end)
            {
                lazy[node * 2].flag = true;
                lazy[node * 2].val += lazy[node].val;

                lazy[node * 2 + 1].flag = true;
                lazy[node * 2 + 1].val += lazy[node].val;
            }

            tree[node] += (end - start + 1) * lazy[node].val;
            lazy[node].flag = false;
            lazy[node].val = 0;
        }
    }

    void update(int pos, value_type val)
    {
        inner_update(1, 0, data_count - 1, pos, pos, val);
    }

    void update(int left, int right, value_type val)
    {
        inner_update(1, 0, data_count - 1, left, right, val);
    }

    void inner_update(int node, int start, int end, int left, int right, value_type val)
    {
        propagate(node, start, end);

        if (right < start || end < left) return;
        if (left <= start && end <= right)
        {
            lazy[node].flag = true;
            lazy[node].val += val;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        inner_update(node * 2, start, mid, left, right, val);
        inner_update(node * 2 + 1, mid + 1, end, left, right, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    value_type query(int pos)
    {
        return inner_query(1, 0, data_count - 1, pos, pos);
    }

    value_type query(int left, int right)
    {
        return inner_query(1, 0, data_count - 1, left, right);
    }

    value_type inner_query(int node, int start, int end, int left, int right)
    {
        propagate(node, start, end);

        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        return inner_query(node * 2, start, mid, left, right) + inner_query(node * 2 + 1, mid + 1, end, left, right);
    }
};

//segment_tree_lazy<int> seg(N);
//seg.data_list[i] = val;
//seg.init();
//seg.update(pos, val);
//seg.update(left, right, val);
//int ret1 = seg.query(pos);
//int ret2 = seg.query(left, right);