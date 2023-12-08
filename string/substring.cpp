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

using namespace std;

namespace string_helper
{
    bool start_with(const string& s1, const string& s2)
    {
        if (s1.size() >= s2.size() && s1.compare(0, s2.size(), s2) == 0)
        {
            return true;
        }

        return false;
    }
};

//bool ret = string_helper::start_with(s1, s2);