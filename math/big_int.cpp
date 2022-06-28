#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

class big_int
{
public:
    string digit;

public:
    big_int()
        : digit()
    {}

    big_int(string _digit)
        : digit(_digit)
    {}

public:
    bool operator ==(const big_int& o) const
    {
        return (digit == o.digit);
    }

    bool operator !=(const big_int& o) const
    {
        return !(digit == o.digit);
    }

    big_int operator +(const big_int& o) const
    {
        size_t left_size = digit.size();
        size_t right_size = o.digit.size();

        big_int sum;

        int value = 0;
        while (left_size > 0 || right_size > 0 || value > 0)
        {
            if (left_size > 0)
            {
                value += digit[left_size - 1] - '0';
                left_size--;
            }
            if (right_size > 0)
            {
                value += o.digit[right_size - 1] - '0';
                right_size--;
            }

            sum.digit.push_back((value % 10) + '0');
            value /= 10;
        }

        reverse(sum.digit.begin(), sum.digit.end());
        return sum;
    }
};

//big_int b1("1");
//big_int ret = b1 + b2;