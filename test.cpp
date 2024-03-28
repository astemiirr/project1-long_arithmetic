//test.cpp
#include "test.hpp"

namespace mynamespace{

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

	clock_t start_time = clock();

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

	clock_t finish_time = clock();

	test.time = ((double) (finish_time - start_time)) * 1000 / CLOCKS_PER_SEC;
	test.correct_res = correct_res;
	test.op = op;
	test.correct = (test.correct_res == test.res);

	return test;
}

void show_test_ress(const std::vector <TestT>& tests) {
	int results = 0;

	for (int i = 0; i < tests.size(); ++i) {
		results += tests[i].correct;

		std::cout << "Test" << (i + 1) << ". ";

		if (tests[i].correct) {
			std::cout << "OK (" << tests[i].time << " ms)";
		}
		else {
			std::cout << "Failed: ";

            std::cout << tests[i].op1 << " " << tests[i].op << " " << tests[i].op2 << " = " << tests[i].correct_res << " != " << tests[i].res;
		}
		
		std::cout << std::endl;
	}

	std::cout << "..........................." << std::endl;
	std::cout << results << " / " << tests.size() << std::endl << std::endl;
}

void addTest() {
	std::vector <TestT> adds;

	adds.push_back(testing('+', big_real(0), big_real(0), big_real(0)));
	adds.push_back(testing('+', big_real(0), big_real(23), big_real(23)));
	adds.push_back(testing('+', big_real(-49), big_real(49), big_real(0)));
	adds.push_back(testing('+', big_real("53.5"), big_real("1.056"), big_real("54.556")));
	adds.push_back(testing('+', big_real("5"), big_real("0.000000001"), big_real("5.000000001")));
	adds.push_back(testing('+', big_real("3.14159"), big_real("0.00000265357989"), big_real("3.14159265357989")));
	adds.push_back(testing('+', big_real(-12), big_real(25), big_real(13)));
	adds.push_back(testing('+', big_real(123456789), big_real(987654321), big_real("1111111110")));
	
	std::cout << "Test of adds big_real" << std::endl;
	show_test_ress(adds);
}

void subTest() {
	std::vector <TestT> subs;

	subs.push_back(testing('-', big_real(0), big_real(0), big_real(0)));
	subs.push_back(testing('-', big_real(0), big_real(33), big_real(-33)));
	subs.push_back(testing('-', big_real(-12), big_real(55), big_real(-67)));
	subs.push_back(testing('-', big_real(19), big_real(9), big_real(10)));
	subs.push_back(testing('-', big_real(15.5), big_real(-2.45), big_real(17.95)));
	subs.push_back(testing('-', big_real("3.14159265357989"), big_real("3.14"), big_real("0.00159265357989")));
	subs.push_back(testing('-', big_real(123456789), big_real(987654321), big_real("-864197532")));
	subs.push_back(testing('-', big_real(-987654321), big_real(123456789), big_real("-1111111110")));

	std::cout << "Test of subs big_real" << std::endl;
	show_test_ress(subs);
}

void multTest() {
	std::vector <TestT> mults;

	mults.push_back(testing('*', big_real(0), big_real(0), big_real(0)));
	mults.push_back(testing('*', big_real(1), big_real(123.5), big_real(123.5)));
	mults.push_back(testing('*', big_real(12), big_real(13), big_real(156)));
	mults.push_back(testing('*', big_real("0.78489816389"), big_real("4"), big_real("3.13959265556")));
	mults.push_back(testing('*', big_real(-12.5), big_real(-2.05), big_real(25.625)));
	mults.push_back(testing('*', big_real(123456789), big_real(987654321), big_real("121932631112635269")));

	std::cout << "Test of mults big_real" << std::endl;
	show_test_ress(mults);
}

void divTest() {
	std::vector <TestT> divs;

	divs.push_back(testing('/', big_real(0), big_real(-3), big_real(0)));
	divs.push_back(testing('/', big_real(1), big_real(4), big_real(0.25)));
	divs.push_back(testing('/', big_real(1), big_real(0.125), big_real(8)));
	divs.push_back(testing('/', big_real(12345), big_real(800), big_real(15.43125)));
	divs.push_back(testing('/', big_real("1"), big_real("1000000"), big_real("0.000001")));
	divs.push_back(testing('/', big_real("-121932631112635269"), big_real("-987654321"), big_real("123456789")));

	std::cout << "Test of divs big_real" << std::endl;
	show_test_ress(divs);
}

}
