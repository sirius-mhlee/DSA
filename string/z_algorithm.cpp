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

class z_algorithm
{
public:
    vector<int> z_array;

    vector<int> result;

public:
    z_algorithm(string text, string pattern)
        : z_array(), result()
    {
        process_z_array(pattern + "$" + text);

        int pattern_size = (int)pattern.size();
        for (int i = pattern_size + 1; i < (int)z_array.size(); i++)
        {
            if (z_array[i] == pattern_size)
                result.push_back(i - (pattern_size + 1));
        }
    }

public:
    void process_z_array(string concat)
    {
        int concat_size = (int)concat.size();
        z_array.assign(concat_size, 0);

        for (int i = 1, l = 0, r = 0; i < concat_size; i++)
        {
            if (i <= r) z_array[i] = min(r - i + 1, z_array[i - l]);

            while (i + z_array[i] < concat_size && concat[z_array[i]] == concat[i + z_array[i]])
                z_array[i]++;

            if (i + z_array[i] - 1 > r)
            {
                l = i;
                r = i + z_array[i] - 1;
            }
        }
    }
};

//z_algorithm z(T, P);
//vector<int> z_array = z.z_array;
//vector<int> ret = z.result;