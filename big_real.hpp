//big_real.hpp
#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class big_real {
	int sign;
	std::vector <int> digits;
	int exponent;

	void removeZeroes();
	void normalize();

	const int divDigits = 200;

public:
	big_real();
	big_real(const big_real& other);
	big_real(double value);
	big_real(const std::string& s_inp);

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

	big_real& operator+=(const big_real& other);
	big_real& operator-=(const big_real& other);
	big_real& operator*=(const big_real& other);
	big_real& operator/=(const big_real& other);

	big_real& operator++();
	big_real& operator--();

	big_real inverse() const;
	std::string tostring() const;
	int fractional_size() const;
	void pi_cut(int value);

	bool isZero() const;

	friend std::ostream& operator<<(std::ostream& outs, const big_real& value);
};
