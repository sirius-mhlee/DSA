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

class big_integer
{
private:
    const long long FLOOR_SQRT_LLONG_MAX = 3037000499;

public:
    char sign;
    string value;

public:
    big_integer()
        : sign{'+'}, value{"0"}
    {}

    big_integer(string num)
    {
        if ((num[0] == '+') || (num[0] == '-'))
        {
            sign = num[0];
            value = num.substr(1);
        }
        else
        {
            sign = '+';
            value = num;
        }

        big_integer::strip_leading_zeroes(value);
    }

public:
    string to_output() const
    {
        if ((sign == '-') && (value != "0")) return ("-" + value);
        else return value;
    }

private:
    static void strip_leading_zeroes(string& value)
    {
        size_t i = 0;
        for (i = 0; i < value.size(); i++)
        {
            if (value[i] != '0') break;
        }

        if (i == value.size()) value = "0";
        else value = value.substr(i);
    }

    static void add_leading_zeroes(string& value, size_t zero_count)
    {
        value = string(zero_count, '0') + value;
    }

    static void add_trailing_zeroes(string& value, size_t zero_count)
    {
        value += string(zero_count, '0');
    }

    static tuple<string, string> get_larger_and_smaller(const string& value1, const string& value2)
    {
        string larger, smaller;
        if ((value1.size() > value2.size()) || ((value1.size() == value2.size()) && (value1 > value2)))
        {
            larger = value1;
            smaller = value2;
        }
        else
        {
            larger = value2;
            smaller = value1;
        }
        big_integer::add_leading_zeroes(smaller, larger.size() - smaller.size());

        return make_tuple(larger, smaller);
    }

    static bool is_power_of_10(const string& value)
    {
        if (value[0] != '1') return false;

        for (size_t i = 1; i < value.size(); i++)
        {
            if (value[i] != '0') return false;
        }

        return true;
    }

public:
    big_integer operator+() const
    {
        return (*this);
    }

    big_integer operator-() const
    {
        big_integer num(value);
        if (num.value != "0")
        {
            if (sign == '+') num.sign = '-';
            else num.sign = '+';
        }
        return num;
    }

    big_integer& operator=(const big_integer& num)
    {
        sign = num.sign;
        value = num.value;
        return (*this);
    }

    bool operator==(const big_integer& num) const
    {
        return ((sign == num.sign) && (value == num.value));
    }

    bool operator!=(const big_integer& num) const
    {
        return !((*this) == num);
    }

    bool operator<(const big_integer& num) const
    {
        if (sign == num.sign)
        {
            if (sign == '+')
            {
                if (value.length() == num.value.length()) return (value < num.value);
                else return (value.length() < num.value.length());
            }
            else
            {
                return (-(*this) > -num);
            }
        }
        else
        {
            return (sign == '-');
        }
    }

    bool operator>(const big_integer& num) const
    {
        return !(((*this) < num) || ((*this) == num));
    }

    bool operator<=(const big_integer& num) const
    {
        return ((*this) < num) || ((*this) == num);
    }

    bool operator>=(const big_integer& num) const
    {
        return !((*this) < num);
    }

public:
    big_integer operator+(const big_integer& num) const
    {
        if ((sign == '+') && (num.sign == '-'))
        {
            big_integer rhs = num;
            rhs.sign = '+';
            return ((*this) - rhs);
        }
        else if ((sign == '-') && (num.sign == '+'))
        {
            big_integer lhs = (*this);
            lhs.sign = '+';
            return -(lhs - num);
        }

        string larger, smaller;
        tie(larger, smaller) = big_integer::get_larger_and_smaller(value, num.value);

        big_integer result;
        result.value = "";

        int carry = 0;
        for (int i = static_cast<int>(larger.size() - 1); i >= 0; i--)
        {
            int sum = (larger[i] - '0') + (smaller[i] - '0') + carry;
            result.value = to_string(sum % 10) + result.value;
            carry = sum / 10;
        }
        if (carry != 0) result.value = to_string(carry) + result.value;

        if ((sign == '-') && (result.value != "0")) result.sign = '-';

        return result;
    }

    big_integer operator-(const big_integer& num) const
    {
        if ((sign == '+') && (num.sign == '-'))
        {
            big_integer rhs = num;
            rhs.sign = '+';
            return ((*this) + rhs);
        }
        else if ((sign == '-') && (num.sign == '+'))
        {
            big_integer lhs = (*this);
            lhs.sign = '+';
            return -(lhs + num);
        }

        big_integer result;
        result.value = "";

        string larger, smaller;
        if (big_integer::abs(*this) > big_integer::abs(num))
        {
            larger = value;
            smaller = num.value;
            if (sign == '-') result.sign = '-';
        }
        else
        {
            larger = num.value;
            smaller = value;
            if (num.sign == '+') result.sign = '-';
        }
        big_integer::add_leading_zeroes(smaller, larger.size() - smaller.size());

        for (int i = static_cast<int>(larger.size() - 1); i >= 0; i--)
        {
            int diff = (larger[i] - smaller[i]);
            if (diff < 0)
            {
                int j = 0;
                for (j = i - 1; j >= 0; j--)
                {
                    if (larger[j] != '0')
                    {
                        larger[j]--;
                        break;
                    }
                }

                j++;
                while (j != i)
                {
                    larger[j] = '9';
                    j++;
                }

                diff += 10;
            }
            result.value = to_string(diff) + result.value;
        }

        big_integer::strip_leading_zeroes(result.value);

        if (result.value == "0") result.sign = '+';

        return result;
    }

    big_integer operator*(const big_integer& num) const
    {
        if (((*this) == big_integer()) || (num == big_integer())) return big_integer();
        if ((*this) == big_integer("1")) return num;
        if (num == big_integer("1")) return (*this);

        big_integer product;

        if (big_integer::abs(*this) <= big_integer(to_string(FLOOR_SQRT_LLONG_MAX)) && big_integer::abs(num) <= big_integer(to_string(FLOOR_SQRT_LLONG_MAX)))
        {
            product = big_integer(to_string(stoll(value) * stoll(num.value)));
        }
        else if (big_integer::is_power_of_10(value))
        {
            product.value = num.value;
            product.value.append(value.begin() + 1, value.end());
        }
        else if (big_integer::is_power_of_10(num.value))
        {
            product.value = value;
            product.value.append(num.value.begin() + 1, num.value.end());
        }
        else
        {
            string larger, smaller;
            tie(larger, smaller) = big_integer::get_larger_and_smaller(value, num.value);

            size_t half_length = larger.size() / 2;
            size_t half_length_ceil = static_cast<size_t>(ceil(larger.size() / 2.0));

            big_integer num1_high(larger.substr(0, half_length));
            big_integer num1_low(larger.substr(half_length));

            big_integer num2_high(smaller.substr(0, half_length));
            big_integer num2_low(smaller.substr(half_length));

            big_integer::strip_leading_zeroes(num1_high.value);
            big_integer::strip_leading_zeroes(num1_low.value);
            big_integer::strip_leading_zeroes(num2_high.value);
            big_integer::strip_leading_zeroes(num2_low.value);

            big_integer prod_high = num1_high * num2_high;
            big_integer prod_low = num1_low * num2_low;
            big_integer prod_mid = (num1_high + num1_low) * (num2_high + num2_low) - prod_high - prod_low;

            big_integer::add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
            big_integer::add_trailing_zeroes(prod_mid.value, half_length_ceil);

            big_integer::strip_leading_zeroes(prod_high.value);
            big_integer::strip_leading_zeroes(prod_mid.value);
            big_integer::strip_leading_zeroes(prod_low.value);

            product = prod_high + prod_mid + prod_low;
        }

        big_integer::strip_leading_zeroes(product.value);

        if (sign == num.sign) product.sign = '+';
        else product.sign = '-';

        return product;
    }

    big_integer& operator+=(const big_integer& num)
    {
        (*this) = (*this) + num;
        return (*this);
    }

    big_integer& operator-=(const big_integer& num)
    {
        (*this) = (*this) - num;
        return (*this);
    }

    big_integer& operator*=(const big_integer& num)
    {
        (*this) = (*this) * num;
        return (*this);
    }

    big_integer& operator++()
    {
        (*this) += big_integer("1");
        return (*this);
    }

    big_integer& operator--()
    {
        (*this) -= big_integer("1");
        return (*this);
    }

    big_integer operator++(int)
    {
        big_integer temp = (*this);
        (*this) += big_integer("1");
        return temp;
    }

    big_integer operator--(int)
    {
        big_integer temp = (*this);
        (*this) -= big_integer("1");
        return temp;
    }

public:
    static big_integer abs(const big_integer& num)
    {
        if (num < big_integer()) return -num;
        else return +num;
    }
};

//big_integer b1("1");
//big_integer b2("2");
//++b1;
//--b1;
//b1++;
//b1--;
//+b1;
//-b1;
//b1 = b2;
//b1 += b2;
//b1 -= b2;
//b1 *= b2;
//b1 + b2;
//b1 - b2;
//b1 * b2;
//b1 == b2;
//b1 != b2;
//b1 < b2;
//b1 > b2;
//b1 <= b2;
//b1 >= b2;
//big_integer abs_result = big_integer::abs(b1);
//string output_result = b1.to_output();