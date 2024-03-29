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

#include <map>

using namespace std;

template<typename value_type>
class notation_convert
{
public:
    int base;
    map<char, int> digit_value;
    map<int, char> value_digit;

public:
    notation_convert(int _base)
        : base(_base), digit_value(), value_digit()
    {
        for (char ch = '0'; ch <= '9'; ch++)
        {
            digit_value[ch] = ch - '0';
            value_digit[ch - '0'] = ch;
        }

        for (char ch = 'A'; ch <= 'Z'; ch++)
        {
            digit_value[ch] = ch - 'A' + 10;
            value_digit[ch - 'A' + 10] = ch;
        }
        
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            digit_value[ch] = ch - 'a' + 10;
            value_digit[ch - 'a' + 10] = ch;
        }
    }

public:
    // base진수 -> 10진수
    value_type convert_from(string value)
    {
        value_type ret = 0;

        reverse(value.begin(), value.end());

        value_type curr_base_value = 1;
        for (char ch : value)
        {
            ret += digit_value[ch] * curr_base_value;
            curr_base_value *= base;
        }

        return ret;
    }

    // 10진수 -> base진수
    string convert_to(value_type value)
    {
        if (value == 0) return "0";

        string ret = "";

        while (value > 0)
        {
            ret += value_digit[value % base];
            value /= base;
        }

        reverse(ret.begin(), ret.end());

        return ret;
    }
};

//notation_convert<long long> nc(base);
//string result1 = nc.convert_to(value);
//long long result2 = nc.convert_from("0");