//test.hpp
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "big_real.hpp"

namespace mynamespace{

struct TestT;

TestT testing(char op, const big_real &op1, const big_real &op2, const big_real &correct_res);

void show_test_ress(const std::vector <TestT>& tests);

void addTest();

void subTest();

void multTest();

void divTest();

}
