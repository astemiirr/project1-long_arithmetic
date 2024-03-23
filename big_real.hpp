//big_real.hpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class big_real {
	const int DivDigits = 1000;

	int sign;
	std::vector<int> digits;
	int dot;

	void remove_extra_zeroes();
	void normalize();
	std::string tostring();

public:
	big_real();
	big_real(const big_real& other);
	big_real(double value);
	big_real(const std::string& s_inp);

	big_real& operator=(const big_real& other);
	big_real operator-() const;

	bool operator==(const big_real& other) const;
	bool operator!=(const big_real& other) const;
	bool operator>(const big_real& other) const;
	bool operator<(const big_real& other) const;

	big_real operator+(const big_real& other) const;
	big_real operator-(const big_real& other) const;
	big_real operator*(const big_real& other) const;
	big_real operator/(const big_real& other) const;

	big_real inverse() const;

	bool isZero() const;
};
