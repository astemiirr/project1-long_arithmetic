//big_real.hpp
#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace mynamespace{

class big_real {
	int sign;
	std::vector <int> digits;
	int dot;

	void removeZeroes();

	const int divDigits = 1000;
	const int sqrtDigits = 100;

public:
	big_real();
	big_real(const big_real& other);
	explicit big_real(double value);
	explicit big_real(const std::string& s_inp);

	big_real& operator=(const big_real& other);

	bool operator>(const big_real& other) const;
	bool operator<(const big_real& other) const;
	bool operator>=(const big_real& other) const;
	bool operator<=(const big_real& other) const;
	bool operator==(const big_real& other) const;
	bool operator!=(const big_real& other) const;

	big_real operator-() const;

	big_real operator+(const big_real& other) const;
	big_real operator-(const big_real& other) const;
	big_real operator*(const big_real& other) const;
	big_real operator/(const big_real& other) const;
	big_real sqrt() const;
	big_real pow(const big_real& p) const;

	big_real& operator+=(const big_real& other);
	big_real& operator-=(const big_real& other);
	big_real& operator*=(const big_real& other);
	big_real& operator/=(const big_real& other);

	big_real& operator++();
	big_real& operator--();

	big_real inverse() const;
	big_real abs() const;
	std::string tostring() const;
	void truncing();
	void end_cut(const int value);
	void spec_movement();

	bool isZero() const;
	bool isInteger() const;
	bool isOdd() const;

	friend std::ostream& operator<<(std::ostream& outs, const big_real& value);
};

}
