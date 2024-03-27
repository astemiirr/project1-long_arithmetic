//test.cpp
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "big_real.hpp"

using namespace std;

struct TestT {
	big_real op1;
	big_real op2;
	big_real res;
	big_real correct_res;

	char op;
	bool correct;
	double time;
};

TestT testing(char op, const big_real &op1, const big_real &op2, const big_real &correct_res) {
	TestT test;

	test.op1 = op1;
	test.op2 = op2;

	clock_t t0 = clock();

	switch (op) {
		case '+':
			test.res = op1 + op2;
			break;
		
		case '-':
			test.res = op1 - op2;
			break;
		
		case '*':
			test.res = op1 * op2;
			break;

		case '/':
			test.res = op1 / op2;
	}

	clock_t t1 = clock();

	test.time = ((double) (t1 - t0)) * 1000 / CLOCKS_PER_SEC;
	test.correct_res = correct_res;
	test.op = op;
	test.correct = (test.correct_res == test.res);

	return test;
}

void show_test_ress(const vector <TestT>& tests) {
	int results = 0;

	for (int i = 0; i < tests.size(); ++i) {
		results += tests[i].correct;

		cout << "Test" << (i + 1) << ". ";

		if (tests[i].correct) {
			cout << "OK (" << tests[i].time << " ms)";
		}
		else {
			cout << "Failed: ";

            cout << tests[i].op1 << " " << tests[i].op << " " << tests[i].op2 << " = " << tests[i].correct_res << " != " << tests[i].res;
		}
		
		cout << endl;
	}

	cout << "-----------------------------" << endl;
	cout << results << " / " << tests.size() << " (" << (100 * results / tests.size()) << "%)" << endl << endl;
}

void addTest() {
	vector <TestT> adds;

	adds.push_back(testing('+', 0, 0, 0));
	adds.push_back(testing('+', 0, 23, 23));
	adds.push_back(testing('+', -49, 49, 0));
	adds.push_back(testing('+', big_real("53.5"), big_real("1.056"), big_real("54.556")));
	adds.push_back(testing('+', big_real("5"), big_real("0.000000001"), big_real("5.000000001")));
	adds.push_back(testing('+', big_real("3.14159"), big_real("0.00000265357989"), big_real("3.14159265357989")));
	adds.push_back(testing('+', -12, 25, 13));
	adds.push_back(testing('+', 123456789, 987654321, big_real("1111111110")));
	
	cout << "Test of adds big_real" << endl;
	show_test_ress(adds);
}

void subTest() {
	vector <TestT> subs;

	subs.push_back(testing('-', 0, 0, 0));
	subs.push_back(testing('-', 0, 33, -33));
	subs.push_back(testing('-', -12, 55, -67));
	subs.push_back(testing('-', 19, 9, 10));
	subs.push_back(testing('-', 15.5, -2.45, 17.95));
	subs.push_back(testing('-', big_real("3.14159265357989"), big_real("3.14"), big_real("0.00159265357989")));
	subs.push_back(testing('-', 123456789, 987654321, big_real("-864197532")));
	subs.push_back(testing('-', -987654321, 123456789, big_real("-1111111110")));

	cout << "Test of subs big_real" << endl;
	show_test_ress(subs);
}

void multTest() {
	vector <TestT> mults;

	mults.push_back(testing('*', 0, 0, 0));
	mults.push_back(testing('*', 1, 123.5, 123.5));
	mults.push_back(testing('*', 12, 13, 156));
	mults.push_back(testing('*', big_real("0.78489816389"), big_real("4"), big_real("3.13959265556")));
	mults.push_back(testing('*', -12.5, -2.05, 25.625));
	mults.push_back(testing('*', 123456789, 987654321, big_real("121932631112635269")));

	cout << "Test of mults big_real" << endl;
	show_test_ress(mults);
}

void divTest() {
	vector <TestT> divs;

	divs.push_back(testing('/', 0, 5, 0));
	divs.push_back(testing('/', 0, -3, 0));
	divs.push_back(testing('/', 1, 4, 0.25));
	divs.push_back(testing('/', 1, 0.125, 8));
	divs.push_back(testing('/', 77777, 7, 11111));
	divs.push_back(testing('/', 12345, 800, 15.43125));
	divs.push_back(testing('/', big_real("1"), big_real("1000000"), big_real("0.000001")));
	divs.push_back(testing('/', big_real("-121932631112635269"), big_real("-987654321"), big_real("123456789")));

	cout << "Test of divs big_real" << endl;
	show_test_ress(divs);
}
