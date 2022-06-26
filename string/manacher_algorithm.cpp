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

class manacher_algorithm
{
public:
    string expand_text;

    vector<int> result;

public:
    manacher_algorithm(string text)
        : expand_text(), result()
    {
        expand_text.push_back(text[0]);
        for (int i = 1; i < (int)text.size(); i++)
        {
            expand_text.push_back('$');
            expand_text.push_back(text[i]);
        }

        process(expand_text);
    }

public:
    void process(string expand)
    {
        int expand_size = (int)expand.size();
        result.assign(expand_size, 0);

        for (int i = 1, length = 0, r = 0; i < expand_size; i++)
        {
            if (i <= r) result[i] = min(r - i, result[2 * length - i]);

            while (i - result[i] - 1 >= 0 && i + result[i] + 1 < expand_size && expand[i - result[i] - 1] == expand[i + result[i] + 1])
                result[i]++;

            if (i + result[i] > r)
            {
                length = i;
                r = i + result[i];
            }
        }
    }
};

//manacher_algorithm ma(T);
//vector<int> ret = ma.result;