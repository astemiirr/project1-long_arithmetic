// big_real.hpp
#pragma once
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

    big_real();

    big_real(const big_real &other);

    /*explicit */ big_real(string s);

    big_real operator+(const big_real &other);

    bool operator==(const big_real &other) /*const*/;

    bool operator!=(const big_real &other);

    bool operator>(const big_real &other);

    bool operator<(const big_real &other);

    big_real operator-(const big_real &other);

    // big_real operator*(const big_real& other);

    // Additional functions
    void remove_extra_zeroes();

    void print();
};