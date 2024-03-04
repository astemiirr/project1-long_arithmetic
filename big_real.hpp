// big_real.hpp
#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class big_real
{
private:
    int SIZE = 100;

public:
    std::vector<int> vec;
    int digits[SIZE];
    int comma;
    bool is_negative;

    big_real(){
        for (int i = 0; i < SIZE; ++i)
        {
            digits[i] = 0;
        }
        comma = 0;
        is_negative = 0;
    }

    big_real(const big_real &other){
        for (int i = 0; i < SIZE; ++i)
        {
            digits[i] = other.digits[i];
        }
        comma = other.comma;
        is_negative = other.is_negative;
    }

    /*explicit */ big_real(string s){
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

    big_real operator+(const big_real &other);

    big_real operator-(const big_real &other);

    // big_real operator*(const big_real& other);

    bool operator==(const big_real &other) /*const*/;

    bool operator!=(const big_real &other);

    bool operator>(const big_real &other);

    bool operator<(const big_real &other);

    // Additional functions
    void remove_extra_zeroes();

    void print();
};
