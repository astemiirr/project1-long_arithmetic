// big_real.cpp
#include "big_real.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class big_real
{
private:
    static const int SIZE = 100;

public:
    int digits[SIZE];
    int comma;
    bool is_negative;
    big_real()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            digits[i] = 0;
        }
        comma = 0;
        is_negative = 0;
    }
    big_real(const big_real &other)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            digits[i] = other.digits[i];
        }
        comma = other.comma;
        is_negative = other.is_negative;
    }
    /*explicit */ big_real(string s)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            digits[i] = 0;
        }
        comma = 0;
        is_negative = 0;
        if (s[0] == '-')
        {
            is_negative = 1;
            s.erase(0, 1);
        }
        while (!(isdigit(s[s.length() - 1]) || s[s.length() - 1] == '.'))
        {
            s.erase(s.length() - 1);
        }
        if (s.find('e') != string::npos || s.find('E') != string::npos)
        {
            if (s.find('e') != string::npos)
            {
                comma -= stoi(s.substr(s.find('e')));
                s.erase(s.find('e'));
            }
            else
            {
                comma -= stoi(s.substr(s.find('E')));
                s.erase(s.find('E'));
            }
        }
        if (s.find('.') != string::npos)
        {
            while (s[s.length()] == '0')
            {
                s.erase(s.length() - 1);
            }
            comma += (s.length() - 1 - s.find('.'));
            s.erase(s.find('.'), 1); //?
        }

        int ind = 0;
        if (comma < 0)
        {
            ind = abs(comma);
        }
        for (int i = s.length() - 1; i >= 0; --i)
        {
            digits[ind] = (s[i] - '0');
            ++ind;
        }
        big_real Zero;
        is_negative = !is_negative;
        if (*this != Zero)
        {
            is_negative = !is_negative;
        }
    }

    big_real operator+(const big_real &other)
    {
        big_real curr1(*this);
        big_real curr2(other);
        if (curr2.is_negative)
        {
            curr2.is_negative = !curr2.is_negative;
            return curr1 - curr2;
        }
        else if (curr1.is_negative)
        {
            curr1.is_negative = !curr1.is_negative;
            return curr2 - curr1;
        }
        else
        {
            if (curr1.comma < curr2.comma)
            {
                swap(curr1, curr2);
            }
            int comma_diff = curr1.comma - curr2.comma;

            curr1.digits[comma_diff] += curr2.digits[0];
            for (int i = comma_diff + 1; i < SIZE; ++i)
            {
                curr1.digits[i] += curr2.digits[i - comma_diff];
                if (curr1.digits[i - 1] > 9)
                {
                    curr1.digits[i - 1] -= 10;
                    ++curr1.digits[i];
                }
            }
        }
        curr1.remove_extra_zeroes();
        return curr1;
    }

    bool operator==(const big_real &other) /*const*/
    {
        if (is_negative != other.is_negative || comma != other.comma)
        {
            return false;
        }
        for (int i = 0; i < SIZE; ++i)
        {
            if (digits[i] != other.digits[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const big_real &other)
    {
        if (is_negative != other.is_negative || comma != other.comma)
        {
            return true;
        }
        for (int i = 0; i < SIZE; ++i)
        {
            if (digits[i] != other.digits[i])
            {
                return true;
            }
        }
        return false;
    }

    bool operator>(const big_real &other)
    {
        if (other.is_negative && !is_negative)
        {
            return true;
        }
        else if (!other.is_negative && is_negative)
        {
            return false;
        }

        for (int i = 0; i < SIZE; ++i)
        {
            if (digits[i + comma] != other.digits[i + other.comma])
            {
                if (digits[i + comma] > other.digits[i + other.comma])
                {
                    return !is_negative;
                }
                else
                {
                    return is_negative;
                }
            }
        }
        if (comma > other.comma)
        {
            return true;
        }
        else
        {
            for (int i = 0; i < comma; ++i)
            {
                if (digits[i] > other.digits[i])
                {
                    return !is_negative;
                }
                else
                {
                    return is_negative;
                }
            }
        }
        return false;
    }

    bool operator<(const big_real &other)
    {
        return !(*this == other || *this > other);
    }

    big_real operator-(const big_real &other)
    {
        big_real curr1(*this);
        big_real curr2(other);
        if (curr2.is_negative)
        {
            curr2.is_negative = !curr2.is_negative;
            return curr1 + curr2;
        }
        else if (curr1.is_negative)
        {
            curr1.is_negative = !curr1.is_negative;
            big_real curr3 = curr1 + curr2;
            curr3.is_negative = 1;

            big_real Zero;
            curr3.is_negative = !curr3.is_negative;
            if (curr3 != Zero)
            {
                curr3.is_negative = !curr3.is_negative;
            }
            return curr3;
        }
        else if (curr1 < curr2)
        {
            big_real curr3 = curr2 - curr1;
            curr3.is_negative = 1;

            big_real Zero;
            curr3.is_negative = !curr3.is_negative;
            if (curr3 != Zero)
            {
                curr3.is_negative = !curr3.is_negative;
            }
            return curr3;
        }
        else
        {
            int comma_diff = curr1.comma - curr2.comma;

            if (comma_diff == 0)
            {
                curr1.digits[0] -= curr2.digits[0];
            }
            if (comma_diff >= 0)
            {
                for (int i = comma_diff + 1; i < SIZE; ++i)
                {
                    curr1.digits[i] -= curr2.digits[i - comma_diff];
                    if (curr1.digits[i - 1] < 0)
                    {
                        curr1.digits[i - 1] += 10;
                        --curr1.digits[i];
                    }
                }
                curr1.remove_extra_zeroes();
                return curr1;
            }
            else
            {
                big_real curr3;
                int i = 0;
                curr3.digits[i] = -curr2.digits[i];
                ++i;
                while (i < abs(comma_diff))
                {
                    curr3.digits[i] = -curr2.digits[i];
                    if (curr3.digits[i - 1] < 0)
                    {
                        curr3.digits[i - 1] += 10;
                        --curr3.digits[i];
                    }
                    ++i;
                }
                for (; i < SIZE; ++i)
                {
                    curr3.digits[i] = curr1.digits[i + comma_diff] - curr2.digits[i];
                    if (curr3.digits[i - 1] < 0)
                    {
                        curr3.digits[i - 1] += 10;
                        --curr3.digits[i];
                    }
                }
                curr3.comma = max(curr1.comma, curr2.comma);
                curr3.remove_extra_zeroes();
                return curr3;
            }
        }
    }

    // Additional functions //?
    void remove_extra_zeroes()
    {
        int k_extra0 = 0;
        for (int i = 0; i < SIZE && comma > 0; ++i)
        {
            if (digits[i] == 0)
            {
                ++k_extra0;
                --comma;
            }
            else
            {
                break;
            }
        }
        if (k_extra0)
        {
            for (int i = 0; i < SIZE - k_extra0; ++i)
            {
                digits[i] = digits[i + k_extra0];
            }
        }
    }
    void print()
    {
        if (is_negative)
        {
            cout << "-";
        }
        int i = SIZE - 1;
        while (i >= 0 && !digits[i] && i > comma)
        {
            --i;
        }
        if (i < 0)
        {
            cout << "0";
            return;
        }
        for (; i >= comma; --i)
        {
            cout << digits[i];
        }
        if (comma)
        {
            cout << ".";
        }
        for (; i >= 0; --i)
        {
            cout << digits[i];
        }
    }
};