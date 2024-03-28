//big_real.cpp
#include "big_real.hpp"

namespace mynamespace{

void big_real::removeZeroes() {
	// удаление нулей справа
    while (digits[digits.size() - 1] == 0 && digits.size() > 1) {
        digits.erase(digits.end() - 1);
    }
    
    // удаление нулей слева
    while (digits[0] == 0 && digits.size() > 1) {
        digits.erase(digits.begin());
        --dot;
    }

	if (isZero()) {
		dot = 1;
		sign = 1;
	}

	//norm...;
}

void big_real::truncing() {
	if (dot <=0) {
		*this = big_real("0");
	}
	else if(dot < digits.size()) {
		digits.erase(digits.begin() + dot, digits.end());
	}
	//removeZeroes();
}

void big_real::end_cut(const int value) {
	int k = value;
	while(digits.size() > 1 && k > 0) {
		digits.pop_back();
		--dot;
		--k;
	}
}

void big_real::spec_movement() {
	dot = 1;
}

big_real::big_real() {
	sign = 1;
	digits = std::vector<int> (1, 0);
	dot = 1;
}

big_real::big_real(const big_real& other) {
	sign = other.sign;
	dot = other.dot;
	digits = std::vector<int> (other.digits);
}

big_real::big_real(double value) {
	std::stringstream ss;
	ss << std::setprecision(15) << value;

	std::string s_inp = ss.str();
	*this = big_real(s_inp);
}

big_real::big_real(const std::string& s_inp) {
	std::string s = s_inp;

    sign = 1;
    dot = 0;
    if (s[0] == '-') {
        sign = -1;
        s.erase(0, 1);
    }

    while (!(isdigit(s[s.length() - 1]) || s[s.length() - 1] == '.')) {
        s.erase(s.length() - 1);
    }

    if (s.find('e') != std::string::npos) {
        dot += stoi(s.substr(s.find('e')));
        s.erase(s.find('e'));
    }
    else if(s.find('E') != std::string::npos) {
        dot += stoi(s.substr(s.find('E')));
        s.erase(s.find('E'));
    }

    if (s.find('.') != std::string::npos) {
        dot += (s.find('.'));
        s.erase(s.find('.'), 1);
    }
    else {
        dot += s.length();
    }

    for (int i = 0; i < s.length(); ++i) {
        digits.push_back(s[i] - '0');
    }

    removeZeroes();
}

big_real& big_real::operator=(const big_real& other) {
	if (this == &other) {
		return *this;
	}

	sign = other.sign;
	dot = other.dot;
	digits = std::vector<int>(other.digits);

	return *this;
}

bool big_real::operator==(const big_real& other) const {
	if (sign != other.sign || dot != other.dot || digits.size() != other.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i])
        {
            return false;
        }
    }
    return true;
}

bool big_real::operator!=(const big_real& other) const {
	return !(*this == other);
}

bool big_real::operator>(const big_real& other) const {
	if (sign != other.sign) {
		return sign > other.sign;
	}

	if (dot != other.dot) {
		return (dot > other.dot) ^ (sign == -1);
	}

	for (int i = 0; i < digits.size(); ++i) {
        if(other.digits.size() < i + 1){
            return sign == 1;
        }

        if (digits[i] != other.digits[i]) {
            if (digits[i] > other.digits[i]) {
                return sign == 1;
            }
            else {
                return sign == -1;
            }
        }
    }
    
    if(digits.size() < other.digits.size()){
        return sign == -1;
    }

    return false;
}

bool big_real::operator<(const big_real& other) const {
	return !(*this > other || *this == other);
}

bool big_real::operator>=(const big_real& other) const {
	return *this > other || *this == other;
}

bool big_real::operator<=(const big_real& other) const {
	return *this < other || *this == other;
}

big_real big_real::operator-() const {
	big_real res(*this);
	res.sign = -sign;

	return res;
}

big_real big_real::operator+(const big_real& other) const {
	if (sign == other.sign) {
		int exp1 = dot;
		int exp2 = other.dot;

		std::vector <int> v1(digits);
		std::vector <int> v2(other.digits);

		while (exp1 != std::max(exp1, exp2) || exp2 != std::max(exp1, exp2)) {
			if (exp1 != std::max(exp1, exp2)) {
				v1.insert(v1.begin(), 0);
				++exp1;
			}
			if (exp2 != std::max(exp1, exp2)) {
				v2.insert(v2.begin(), 0);
				exp2++;
			}
		}

		int size = std::max(v1.size(), v2.size());

		while (v1.size() != size) {
			v1.push_back(0);
		}

		while (v2.size() != size) {
			v2.push_back(0);
		}

		big_real res;

		res.sign = sign;
		res.digits = std::vector<int> (size + 1, 0);

		for (int i = 0; i < size; ++i) {
			res.digits[i + 1] = v1[i] + v2[i];
		}

		for (int i = size; i > 0; --i) {
			res.digits[i - 1] += res.digits[i] / 10;
			res.digits[i] %= 10;
		}

		res.dot = std::max(exp1, exp2) + 1;
		res.removeZeroes();

		return res;
	}

	if (sign == -1) {
		return other - (-(*this));
	}
	
	return *this - (-other);
}

big_real big_real::operator-(const big_real& other) const {
	if (sign == 1 && other.sign == 1) {
		int exp1 = *this > other ? dot : other.dot;
		int exp2 = *this > other ? other.dot : dot;

		std::vector <int> v1(*this > other ? digits : other.digits);
		std::vector <int> v2(*this > other ? other.digits : digits);

		while (exp1 != std::max(exp1, exp2)) {
			v1.insert(v1.begin(), 0);
			++exp1;
		}
		while (exp2 != std::max(exp1, exp2)) {
			v2.insert(v2.begin(), 0);
			++exp2;
		}

		int size = std::max(v1.size(), v2.size());

		while (v1.size() != size) {
			v1.push_back(0);
		}

		while (v2.size() != size) {
			v2.push_back(0);
		}

		big_real res;

		res.sign = *this > other ? 1 : -1;
		res.digits = std::vector<int> (size + 1, 0);

		for (int i = 0; i < size; ++i) {
			res.digits[i + 1] = v1[i] - v2[i];
		}

		for (int i = size; i > 0; --i) {
			if (res.digits[i] < 0) {
				res.digits[i] += 10;
				--res.digits[i - 1];
			}
		}

		res.dot = std::max(exp1, exp2) + 1;
		res.removeZeroes();

		return res;
	}

	if (sign == -1 && other.sign == -1)
		return (-other) - (-(*this));
	
	return *this + (-other);
}

big_real big_real::operator*(const big_real& other) const {
	int len = digits.size() + other.digits.size();

	big_real res;

	res.sign = sign * other.sign;
	res.digits = std::vector<int> (len, 0);
	res.dot = dot + other.dot;

	for (int i = 0; i < digits.size(); ++i) {
		for (int j = 0; j < other.digits.size(); ++j) {
			res.digits[i + j + 1] += digits[i] * other.digits[j];
		}
	}

	for (int i = len - 1; i > 0; --i) {
		res.digits[i - 1] += res.digits[i] / 10;
		res.digits[i] %= 10;
	}

	res.removeZeroes();

	return res;
}

big_real big_real::operator/(const big_real& other) const {
	big_real res = *this * other.inverse();

	int before_dot = std::max(0, dot);

	if (before_dot > res.digits.size() - 1) {
		return res;
	}

	int i = res.digits.size() - 1 - before_dot;
	int n = std::max(0, res.dot);

	if (i > n && res.digits[i] == 9) {
		while (i > n && res.digits[i] == 9) {
			--i;
		}

		if (res.digits[i] == 9) {
			res.digits.erase(res.digits.begin() + n, res.digits.end());
			res = res + big_real(res.sign);
		}
		else {
			res.digits.erase(res.digits.begin() + i + 1, res.digits.end());
			++res.digits[i];
		}
	}

	return res;
}

big_real big_real::sqrt() const {
	if (sign == -1) {
		throw std::string("big_real big_real::sqrt() - value is negative!");
	}

	if (isZero()) {
		return big_real("0");
	}

	big_real x0;
	big_real p("0.5");
	big_real res("0.5");
	big_real eps;
	eps.digits = std::vector<int> (1, 1);
	eps.dot = 1 - sqrtDigits;

	do {
		x0 = res;
		res = p * (x0 + *this / x0);
	} while ((x0 - res).abs() > eps);

	res.digits.erase(res.digits.begin() + std::max(0, res.dot) + sqrtDigits, res.digits.end());
	res.removeZeroes();

	return res;
}

big_real big_real::pow(const big_real& p) const{
	if (!p.isInteger()) {
		throw std::string("big_real big_real::pow(const big_real& p) - p is not integer!");
	}

	big_real res("1");
	big_real a = p.sign == 1 ? *this : this->inverse();
	big_real power = p.abs();

	while (power > big_real("0")) {
		if (power.isOdd()) {
			res *= a;
		}

		a *= a;
		power /= big_real("2");

		if (!power.isInteger()) {
			power.digits.erase(power.digits.end() - 1);
		}
	}

	res.removeZeroes();

	return res;
}

big_real& big_real::operator+=(const big_real& other) {
	return (*this = *this + other);
}
	
big_real& big_real::operator-=(const big_real& other) {
	return (*this = *this - other);
}

big_real& big_real::operator*=(const big_real& other) {
	return (*this = *this * other);
}

big_real& big_real::operator/=(const big_real& other) {
	return (*this = *this / other);
}

big_real& big_real::operator++() {
	return (*this = *this + big_real("1"));
}

big_real& big_real::operator--() {
	return (*this = *this - big_real("1"));
}

big_real big_real::inverse() const {
	if (isZero()) {
		throw std::string("big_real big_real::inverse() - You can't divide by zero!");
	}

	big_real other(*this);
	other.sign = 1;

	big_real t("1");

	big_real res;
	res.sign = sign;
	res.dot = 1;
	res.digits = std::vector<int> ();

	while (other < big_real("1")) {
		++other.dot;
		++res.dot;
	}

	while (t < other) {
		++t.dot;
	}
	
	res.dot -= t.dot - 1;

	int numbers = 0;
	int before_dot = std::max(0, res.dot);
	int maxNumbers = divDigits/* + before_dot*/;

	do {
		int div = 0;

		while (t >= other) {
			++div;
			t -= other;
		}

		++t.dot;
		t.removeZeroes();

		res.digits.push_back(div);
		++numbers;
	} while (!t.isZero() && numbers < maxNumbers);

	return res;
}

big_real big_real::abs() const {
	big_real res(*this);
	res.sign = 1;

	return res;
}

std::string big_real::tostring() const{
	std::string s_out = "";

	if(sign == -1) {
		s_out += "-";
	}

	int k = dot;
	if(k <= 0) {
		s_out += "0.";
		while(k < 0){
			s_out += "0";
			++k;
		}
	}
	
	s_out += std::to_string(digits[0]);
	for(int i = 1; i < digits.size(); ++i) {
		if(dot == i) {
			s_out += ".";
		}
		s_out += std::to_string(digits[i]);
	}

	return s_out;
}

bool big_real::isZero() const {
	return digits.size() == 1 && digits[0] == 0;
}

bool big_real::isInteger() const {
	if (dot < 0) {
		return false;
	}
	else if(digits.size() <= dot) {
		return true;
	}

	return false;
}

bool big_real::isOdd() const {
	if (!isInteger()) {
		return false;
	}

	if (digits.size() == dot) {
		return digits[digits.size() - 1] % 2 == 1;
	}

	return false;
}

std::ostream& operator<<(std::ostream& outs, const big_real& value) {
	if (value.sign == -1) {
		outs << '-';
	}

	if (value.dot > 0) {
		int i = 0;
		int e = value.dot;

		while(i < value.digits.size() && i < e) {
			outs << value.digits[i++];
		}

		while (i < e) {
			outs << "0";
			++i;
		}

		if (i < value.digits.size()) {
			outs << ".";

			while(i < value.digits.size()) {
				outs << value.digits[i++];
			}
		}
	}
	else if (value.dot == 0) {
		outs << "0.";

		for (int i = 0; i < value.digits.size(); ++i) {
			outs << value.digits[i];
		}
	}
	else {
		outs << "0.";

		for (int i = 0; i < -value.dot; ++i) {
			outs << "0";
		}

		for (int i = 0; i < value.digits.size(); ++i) {
			outs << value.digits[i];
		}
	}

	return outs;
}

}
