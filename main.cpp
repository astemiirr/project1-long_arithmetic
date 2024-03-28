#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "big_real.hpp"
#include "test.hpp"
#include "pi_calculation.hpp"

using namespace mynamespace;

int main() {
	// addTest();
	// subTest();
	// multTest();
	// divTest();

	int prec;
    std::cout << "prec = ";
    std::cin >> prec;

    clock_t start_time = clock();
    big_real pi = pi_chudnovsky(prec);
    std::cout << "Pi with " << prec << " signs after the dot: " << pi << std::endl;
    clock_t finish_time = clock();

    std::cout << "Execution time: " << double(finish_time - start_time) / CLOCKS_PER_SEC << "sec" << std::endl;

	return 0;
}
