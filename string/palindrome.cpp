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
    bool check_palindrome(const string& word)
    {
        if (word.empty()) return true;

        size_t lo = 0;
        size_t hi = word.size() - 1;

        while (lo < hi)
        {
            if (word[lo] != word[hi]) return false;

            lo++;
            hi--;
        }

        return true;
    }
};

//bool ret = string_helper::check_palindrome(s1);