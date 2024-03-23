#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "big_real.hpp"

using namespace std;

string pi(int k) {
	big_real ret;
    int j = 1, i = 1;
    while(ret.digits.size() < k) {
        ret = ret + (double)4 / j;
        j += 2;
        ret = ret - (double)4 / j;
        j += 2;
    }

	return ret.tostring;
}

struct TestOp {
	big_real oper1;
	big_real oper2;
	
	big_real res;
	big_real correct_res;

	char op;
	bool is_correct;
	double time;
};

TestOp ToTest(char op, const big_real &oper1, const big_real &oper2, const big_real &correct_res) {
	TestOp test;

	test.oper1 = oper1;
	test.oper2 = oper2;

	clock_t t0 = clock();

	switch (op) {
		case '+':
			test.res = oper1 + oper2;
			break;
		
		case '-':
			test.res = oper1 - oper2;
			break;
		
		case '*':
			test.res = oper1 * oper2;
			break;

		case '/':
			test.res = oper1 / oper2;
	}

	clock_t t1 = clock();

	test.time = (double(t1 - t0)) * 1000 / CLOCKS_PER_SEC;
	test.correct_res = correct_res;
	test.op = op;
	test.is_correct = (test.correct_res == test.res);

	return test;
}

void show_test_ress(const vector <TestOp>& test_vec) {
	int k_res = 0;

	for (int i = 0; i < test_vec.size(); ++i) {
		k_res += test_vec[i].is_correct;

		cout << "Test" << (i + 1) << "...";

		if (test_vec[i].is_correct) {
			cout << "OK..." << test_vec[i].time << "ms";
		}
		else {
			cout << "Failed...";
			cout << test_vec[i].oper1.tostring << " " << test_vec[i].op << " " << test_vec[i].oper2.tostring << " = " << test_vec[i].correct_res.tostring << " != " << test_vec[i].res.tostring;
		}
		
		cout << endl;
	}

	cout << endl << "..........................." << endl;
	cout << k_res << " / " << test_vec.size() << " (" << (100 * double(k_res) / test_vec.size()) << "%)" << endl << endl;
}

void addTest() {
	vector <TestOp> adds;

	adds.push_back(ToTest('+', 0, 0, 0));

	adds.push_back(ToTest('+', 0, 45, 45));
	adds.push_back(ToTest('+', 45, 0, 45));
	adds.push_back(ToTest('+', 0, -45, -45));
	adds.push_back(ToTest('+', -45, 0, -45));

	adds.push_back(ToTest('+', -45, 45, 0));
	adds.push_back(ToTest('+', 9, 1, 10));
	adds.push_back(ToTest('+', -9, -1, -10));

	adds.push_back(ToTest('+', big_real("27.5"), big_real("1.025"), big_real("28.525")));
	adds.push_back(ToTest('+', big_real("-27.5"), big_real("1.025"), big_real("-26.475")));
	adds.push_back(ToTest('+', big_real("1000"), big_real("0.0001"), big_real("1000.0001")));
	adds.push_back(ToTest('+', big_real("5"), big_real("0.000000001"), big_real("5.000000001")));

	adds.push_back(ToTest('+', big_real("2.7"), big_real("0.018281828"), big_real("2.718281828")));
	adds.push_back(ToTest('+', big_real("3.14159"), big_real("0.00000265357989"), big_real("3.14159265357989")));

	adds.push_back(ToTest('+', -12, 25, 13));
	adds.push_back(ToTest('+', 12, -25, -13));
	adds.push_back(ToTest('+', -12, -25, -37));
	adds.push_back(ToTest('+', 12, 25, 37));

	adds.push_back(ToTest('+', 123456789, 987654321, big_real("1111111110")));
	adds.push_back(ToTest('+', 987654321, 123456789, big_real("1111111110")));
	adds.push_back(ToTest('+', -123456789, 987654321, big_real("864197532")));
	adds.push_back(ToTest('+', -987654321, 123456789, big_real("-864197532")));
	adds.push_back(ToTest('+', -123456789, -987654321, big_real("-1111111110")));
	adds.push_back(ToTest('+', -987654321, -123456789, big_real("-1111111110")));
	
	cout << "Test of adds big_real" << endl;
	show_test_ress(adds);
}

void subTest() {
	vector<TestOp> subs;

	subs.push_back(ToTest('-', 0, 0, 0));

	subs.push_back(ToTest('-', 0, 25, -25));
	subs.push_back(ToTest('-', 0, -25, 25));
	subs.push_back(ToTest('-', -25, 0, -25));
	subs.push_back(ToTest('-', 25, 0, 25));

	subs.push_back(ToTest('-', -12, 25, -37));
	subs.push_back(ToTest('-', 12, -25, 37));
	subs.push_back(ToTest('-', -12, -25, 13));
	subs.push_back(ToTest('-', 12, 25, -13));

	subs.push_back(ToTest('-', 10, 1, 9));
	subs.push_back(ToTest('-', 1000, 1, 999));
	subs.push_back(ToTest('-', -10, 1, -11));

	subs.push_back(ToTest('-', 12.5, 1.45, 11.05));
	subs.push_back(ToTest('-', -12.5, 1.45, -13.95));
	subs.push_back(ToTest('-', 12.5, -1.45, 13.95));
	subs.push_back(ToTest('-', -12.5, -1.45, -11.05));

	subs.push_back(ToTest('-', big_real("3.14159265357989"), big_real("3.14"), big_real("0.00159265357989")));
	subs.push_back(ToTest('-', big_real("2.718281828"), big_real("0.018281828"), big_real("2.7")));
	subs.push_back(ToTest('-', big_real("5.000000001"), big_real("0.000000001"), big_real("5")));

	subs.push_back(ToTest('-', 123456789, 987654321, big_real("-864197532")));
	subs.push_back(ToTest('-', 987654321, 123456789, big_real("864197532")));
	subs.push_back(ToTest('-', -123456789, 987654321, big_real("-1111111110")));
	subs.push_back(ToTest('-', -987654321, 123456789, big_real("-1111111110")));
	subs.push_back(ToTest('-', -123456789, -987654321, big_real("864197532")));
	subs.push_back(ToTest('-', -987654321, -123456789, big_real("-864197532")));

	cout << "Test of subs big_real" << endl;
	show_test_ress(subs);
}

void multTest() {
	vector<TestOp> mults;

	mults.push_back(ToTest('*', 0, 0, 0));
	mults.push_back(ToTest('*', 0, 123.5, 0));
	mults.push_back(ToTest('*', 123.5, 0, 0));
	mults.push_back(ToTest('*', 0, -123.5, 0));
	mults.push_back(ToTest('*', -123.5, 0, 0));

	mults.push_back(ToTest('*', 1, 123.5, 123.5));
	mults.push_back(ToTest('*', 1, -123.5, -123.5));
	mults.push_back(ToTest('*', 123.5, 1, 123.5));
	mults.push_back(ToTest('*', 123.5, -1, -123.5));
	mults.push_back(ToTest('*', -1, -123.5, 123.5));

	mults.push_back(ToTest('*', 12, 13, 156));
	mults.push_back(ToTest('*', -12, 13, -156));
	mults.push_back(ToTest('*', 12, -13, -156));
	mults.push_back(ToTest('*', -12, -13, 156));

	mults.push_back(ToTest('*', 12.5, 2.05, 25.625));
	mults.push_back(ToTest('*', 12.5, -2.05, -25.625));
	mults.push_back(ToTest('*', -12.5, 2.05, -25.625));
	mults.push_back(ToTest('*', -12.5, -2.05, 25.625));

	mults.push_back(ToTest('*', 123456789, 987654321, big_real("121932631112635269")));
	mults.push_back(ToTest('*', 987654321, 123456789, big_real("121932631112635269")));
	mults.push_back(ToTest('*', -123456789, 987654321, big_real("-121932631112635269")));
	mults.push_back(ToTest('*', -987654321, 123456789, big_real("-121932631112635269")));
	mults.push_back(ToTest('*', -123456789, -987654321, big_real("121932631112635269")));
	mults.push_back(ToTest('*', -987654321, -123456789, big_real("121932631112635269")));

	cout << "Test of mults big_real" << endl;
	show_test_ress(mults);
}

void divTest() {
	vector<TestOp> divs;

	divs.push_back(ToTest('/', 0, 5, 0));
	divs.push_back(ToTest('/', 0, 3, 0));
	divs.push_back(ToTest('/', 0, -5, 0));
	divs.push_back(ToTest('/', 0, -3, 0));

	divs.push_back(ToTest('/', 0, 0.125, 0));
	divs.push_back(ToTest('/', 0, 0.0037, 0));
	divs.push_back(ToTest('/', 0, -0.125, 0));
	divs.push_back(ToTest('/', 0, -0.0037, 0));

	divs.push_back(ToTest('/', 1, 2, 0.5));
	divs.push_back(ToTest('/', 1, 4, 0.25));
	divs.push_back(ToTest('/', 1, 5, 0.2));

	divs.push_back(ToTest('/', 1, 0.125, 8));
	divs.push_back(ToTest('/', 1, -0.125, -8));
	divs.push_back(ToTest('/', -1, 0.125, -8));
	divs.push_back(ToTest('/', -1, -0.125, 8));

	divs.push_back(ToTest('/', 3, 5, 0.6));
	divs.push_back(ToTest('/', 3.96, 4, 0.99));
	divs.push_back(ToTest('/', 15, 3, 5));
	divs.push_back(ToTest('/', 45, 6, 7.5));

	divs.push_back(ToTest('/', 6, 3, 2));
	divs.push_back(ToTest('/', 21, 3, 7));
	divs.push_back(ToTest('/', 77777, 7, 11111));

	divs.push_back(ToTest('/', 12345, 800, 15.43125));

	divs.push_back(ToTest('/', big_real("121932631112635269"), big_real("-987654321"), big_real("-123456789")));
	divs.push_back(ToTest('/', big_real("121932631112635269"), big_real("987654321"), big_real("123456789")));
	divs.push_back(ToTest('/', big_real("-121932631112635269"), big_real("987654321"), big_real("-123456789")));
	divs.push_back(ToTest('/', big_real("-121932631112635269"), big_real("-987654321"), big_real("123456789")));

	cout << "Test of divs big_real" << endl;
	show_test_ress(divs);
}

int main() {
	addTest();
	subTest();
	multTest();
	divTest();

	cout << "enter the number of digits for pi...";
	int k;
	cin >> k;

	cout << "pi / start:" << endl;
	double t0 = clock();
	cout << pi(k);
	double t1 = clock();
	cout << "pi / finish" << endl;
	cout << (t1 - t0) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
}
