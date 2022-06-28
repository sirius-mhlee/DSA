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

class suffix_lcp_array
{
public:
    vector<int> suffix_array;
    vector<int> lcp_array;

public:
    suffix_lcp_array(string text)
        : suffix_array(), lcp_array()
    {
        int text_size = (int)text.size();

        suffix_array.assign(text_size, 0);
        lcp_array.assign(text_size, -1);

        vector<int> group(text_size, 0);

        for (int i = 0; i < text_size; i++)
        {
            suffix_array[i] = i;
            group[i] = text[i];
        }

        for (int d = 1; d < text_size; d *= 2)
        {
            auto cmp = [&](int i, int j)->bool
            {
                if (group[i] == group[j])
                {
                    if (i + d < text_size && j + d < text_size)
                        return group[i + d] < group[j + d];
                    else
                        return i > j;
                }
                else
                {
                    return group[i] < group[j];
                }
            };

            sort(suffix_array.begin(), suffix_array.end(), cmp);

            vector<int> next_group(text_size, 0);
            for (int i = 1; i < text_size; i++)
            {
                if (cmp(suffix_array[i - 1], suffix_array[i]))
                    next_group[suffix_array[i]] = next_group[suffix_array[i - 1]] + 1;
                else
                    next_group[suffix_array[i]] = next_group[suffix_array[i - 1]];
            }

            group = next_group;
        }

        int k = 0;
        for (int i = 0; i < text_size; i++)
        {
            if (group[i] == 0) continue;

            for (int j = suffix_array[group[i] - 1]; text[i + k] == text[j + k]; k++);

            lcp_array[group[i]] = k;
            k = max(k - 1, 0);
        }
    }
};

//suffix_lcp_array sla(T);
//vector<int> suffix_array = sla.suffix_array;
//vector<int> lcp_array = sla.lcp_array;