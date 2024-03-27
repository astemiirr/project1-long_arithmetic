//big_real.cpp
#include "big_real.hpp"

using namespace std;

void big_real::removeZeroes() {
	// удаление нулей справа
    while (digits[digits.size() - 1] == 0 && digits.size() > 1) {
        digits.erase(digits.end() - 1);
    }
    
    // удаление нулей слева
    while (digits[0] == 0 && digits.size() > 1) {
        digits.erase(digits.begin());
        --exponent;
    }

	if (isZero()) {
		exponent = 1;
		sign = 1;
	}

	//norm...;
}

big_real::big_real() {
	sign = 1;
	digits = vector<int>(1, 0);
	exponent = 1;
}

big_real::big_real(const big_real& other) {
	sign = other.sign;
	exponent = other.exponent;
	digits = vector<int>(other.digits);
}

big_real::big_real(double value) {
	stringstream ss;
	ss << setprecision(15) << value;

	string s_inp = ss.str();
	*this = big_real(s_inp);
}

big_real::big_real(const string& s_inp) {
	string s = s_inp;

    sign = 1;
    exponent = 0;
    if (s[0] == '-') {
        sign = -1;
        s.erase(0, 1);
    }

    while (!(isdigit(s[s.length() - 1]) || s[s.length() - 1] == '.')) {
        s.erase(s.length() - 1);
    }

    if (s.find('e') != string::npos) {
        exponent += stoi(s.substr(s.find('e')));
        s.erase(s.find('e'));
    }
    else if(s.find('E') != string::npos) {
        exponent += stoi(s.substr(s.find('E')));
        s.erase(s.find('E'));
    }

    if (s.find('.') != string::npos) {
        exponent += (s.find('.'));
        s.erase(s.find('.'), 1);
    }
    else {
        exponent += s.length();
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
	exponent = other.exponent;
	digits = vector<int>(other.digits);

	return *this;
}

bool big_real::operator==(const big_real& other) const {
	if (sign != other.sign || exponent != other.exponent || digits.size() != other.digits.size()) {
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

	if (exponent != other.exponent) {
		return (exponent > other.exponent) ^ (sign == -1);
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
		int exp1 = exponent;
		int exp2 = other.exponent;

		vector <int> v1(digits);
		vector <int> v2(other.digits);

		while (exp1 != max(exp1, exp2) || exp2 != max(exp1, exp2)) {
			if (exp1 != max(exp1, exp2)) {
				v1.insert(v1.begin(), 0);
				++exp1;
			}
			if (exp2 != max(exp1, exp2)) {
				v2.insert(v2.begin(), 0);
				exp2++;
			}
		}

		int size = max(v1.size(), v2.size());

		while (v1.size() != size) {
			v1.push_back(0);
		}

		while (v2.size() != size) {
			v2.push_back(0);
		}

		big_real res;

		res.sign = sign;
		res.digits = vector<int> (size + 1, 0);

		for (int i = 0; i < size; ++i) {
			res.digits[i + 1] = v1[i] + v2[i];
		}

		for (int i = size; i > 0; --i) {
			res.digits[i - 1] += res.digits[i] / 10;
			res.digits[i] %= 10;
		}

		res.exponent = max(exp1, exp2) + 1;
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
		int exp1 = *this > other ? exponent : other.exponent;
		int exp2 = *this > other ? other.exponent : exponent;

		vector <int> v1(*this > other ? digits : other.digits);
		vector <int> v2(*this > other ? other.digits : digits);

		while (exp1 != max(exp1, exp2)) {
			v1.insert(v1.begin(), 0);
			++exp1;
		}
		while (exp2 != max(exp1, exp2)) {
			v2.insert(v2.begin(), 0);
			++exp2;
		}

		int size = max(v1.size(), v2.size());

		while (v1.size() != size) {
			v1.push_back(0);
		}

		while (v2.size() != size) {
			v2.push_back(0);
		}

		big_real res;

		res.sign = *this > other ? 1 : -1;
		res.digits = vector<int> (size + 1, 0);

		for (int i = 0; i < size; ++i) {
			res.digits[i + 1] = v1[i] - v2[i];
		}

		for (int i = size; i > 0; --i) {
			if (res.digits[i] < 0) {
				res.digits[i] += 10;
				--res.digits[i - 1];
			}
		}

		res.exponent = max(exp1, exp2) + 1;
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
	res.digits = vector<int> (len, 0);
	res.exponent = exponent + other.exponent;

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

	int before_dot = max(0, exponent);

	if (before_dot > res.digits.size() - 1) {
		return res;
	}

	int i = res.digits.size() - 1 - before_dot;
	int n = max(0, res.exponent);

	if (i > n && res.digits[i] == 9) {
		while (i > n && res.digits[i] == 9) {
			--i;
		}

		if (res.digits[i] == 9) {
			res.digits.erase(res.digits.begin() + n, res.digits.end());
			res = res + res.sign;
		}
		else {
			res.digits.erase(res.digits.begin() + i + 1, res.digits.end());
			++res.digits[i];
		}
	}

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
	return (*this = *this + 1);
}

big_real& big_real::operator--() {
	return (*this = *this - 1);
}

big_real big_real::inverse() const {
	if (isZero()) {
		throw string("big_real big_real::inverse() - You can't divide by zero!");
	}

	big_real other(*this);
	other.sign = 1;

	big_real t("1");

	big_real res;
	res.sign = sign;
	res.exponent = 1;
	res.digits = vector<int> ();

	while (other < 1) {
		++other.exponent;
		++res.exponent;
	}

	while (t < other) {
		++t.exponent;
	}
	
	res.exponent -= t.exponent - 1;

	int numbers = 0;
	int before_dot = max(0, res.exponent);
	int maxNumbers = divDigits/* + before_dot*/;

	do {
		int div = 0;

		while (t >= other) {
			++div;
			t -= other;
		}

		++t.exponent;
		t.removeZeroes();

		res.digits.push_back(div);
		++numbers;
	} while (!t.isZero() && numbers < maxNumbers);

	return res;
}

string big_real::tostring() const{
	string s_out = "";

	if(sign == -1) {
		s_out += "-";
	}

	int k = exponent;
	if(k <= 0) {
		s_out += "0.";
		while(k < 0){
			s_out += "0";
			++k;
		}
	}
	
	s_out += to_string(digits[0]);
	for(int i = 1; i < digits.size(); ++i) {
		if(exponent == i) {
			s_out += ".";
		}
		s_out += to_string(digits[i]);
	}

	return s_out;
}

int big_real::fractional_size() const{
	return digits.size();
}

void big_real::pi_cut(int value) {
	if(digits.size() > value + 1) {
		digits.erase(digits.begin() + value + 1, digits.end());
	}
}

bool big_real::isZero() const {
	return digits.size() == 1 && digits[0] == 0;
}

ostream& operator<<(ostream& outs, const big_real& value) {
	if (value.sign == -1) {
		outs << '-';
	}

	if (value.exponent > 0) {
		int i = 0;
		int e = value.exponent;

		while(i < value.digits.size() && i < e) {
			outs << value.digits[++i];
		}

		while (i < e) {
			outs << "0";
			++i;
		}

		if (i < value.digits.size()) {
			outs << ".";

			while(i < value.digits.size()) {
				outs << value.digits[++i];
			}
		}
	}
	else if (value.exponent == 0) {
		outs << "0.";

		for (int i = 0; i < value.digits.size(); ++i)
			outs << value.digits[i];
	}
	else {
		outs << "0.";

		for (int i = 0; i < -value.exponent; ++i) {
			outs << "0";
		}

		for (int i = 0; i < value.digits.size(); ++i) {
			outs << value.digits[i];
		}
	}

	return outs;
}
