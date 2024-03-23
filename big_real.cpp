//big_real.cpp
#include "big_real.hpp"

using namespace std;

void big_real::remove_extra_zeroes() {
	// удаление нулей справа
    while (digits.size() > dot && digits[digits.size() - 1] == 0 && digits.size() > 1) {
        digits.erase(digits.end() - 1);
    }
    while (digits[digits.size() - 1] == 0 && digits.size() > 1) {
        digits.erase(digits.end() - 1);
    }
    
    // удаление нулей слева
    while (digits[0] == 0 && dot > 0 && digits.size() > 1) {
        digits.erase(digits.begin());
        --dot;
    }
    while (digits[0] == 0 && dot <= 0 && digits.size() > 1) {
        digits.erase(digits.begin());
        --dot;
    }

    if (digits.size() == 1 && digits[0] == 0) {
        dot = 1;
        sign = 1;
    }

	//normalize();
}

void big_real::normalize() {
	int start = max(dot, 0);
	int realDigits = digits.size() - start;

	if (realDigits >= DivDigits) {
		int count = 0;
		int maxCount = 0;

		int i = start;

		while(i < digits.size()) {
			count = 0;

			while (i < digits.size() && digits[i] == 9) {
				count++;
				i++;
			}
			
			if (count > maxCount)
				maxCount = count;

			i++;
		}
		
		if (maxCount > DivDigits * 4 / 5) {
			i = digits.size() - 1;

			do {
				count = 0;

				while (i > 0 && digits[i] != 9)
					i--;

				while (i > 0 && digits[i] == 9) {
					count++;
					i--;
				}
			} while (count != maxCount);

			digits.erase(digits.begin() + i + 1, digits.end());
			digits[i]++;
		}
	}
}

string big_real::tostring(){
	string s = "";

	if(!sign) {
		s += "-";
	}

	int k = dot;
	if(k <= 0) {
		s += "0.";
		while(k < 0){
			s += "0";
			++k;
		}
	}
	
	s += to_string(digits[0]);
	for(int i = 1; i < digits.size(); ++i) {
		if(dot == i) {
			s += ".";
		}
		s += to_string(digits[i]);
	}

	return s;
}

big_real::big_real() {
    sign = 1;
	digits = vector<int>(1, 0);
	dot = 1;
}

big_real::big_real(const big_real& other) {
	sign = other.sign;
	dot = other.dot;
	digits = vector<int>(other.digits.size());

	for (int i = 0; i < other.digits.size(); ++i) {
		digits[i] = other.digits[i];
	}
}

big_real::big_real(const string& s_inp) {
    string s = s_inp;

    sign = 1;
    dot = 0;
    if (s[0] == '-') {
        sign = 0;
        s.erase(0, 1);
    }

    while (!(isdigit(s[s.length() - 1]) || s[s.length() - 1] == '.')) {
        s.erase(s.length() - 1);
    }

    if (s.find('e') != string::npos) {
        dot += stoi(s.substr(s.find('e')));
        s.erase(s.find('e'));
    }
    else {
        dot += stoi(s.substr(s.find('E')));
        s.erase(s.find('E'));
    }

    if (s.find('.') != string::npos) {
        dot += (s.find('.'));
        s.erase(s.find('.'), 1);
    }
    else {
        dot += s.length();
    }

    for (int i = 0; i < s.length(); ++i) {
        digits.push_back(s[i] - '0');
    }

    remove_extra_zeroes();
}

big_real& big_real::operator=(const big_real& other) {
	if (this == &other) {
		return *this;
	}

	sign = other.sign;
	dot = other.dot;
	digits = vector<int>(other.digits.size());

	for (int i = 0; i < other.digits.size(); i++)
		digits[i] = other.digits[i];

	return *this;
}

big_real::big_real(double value) {
	stringstream ss;
	ss << setprecision(15) << value;
	big_real(ss.str());
}

bool big_real::operator==(const big_real &other) const {
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
bool big_real::operator!=(const big_real &other) const {
    return !(*this == other);
}

bool big_real::operator>(const big_real &other) const {
    if (sign != other.sign) {
        return sign;
    }

    if(dot != other.dot) {
        return (dot > other.dot) ^ (!sign);
    }

    for (int i = 0; i < digits.size(); ++i) {
        if(other.digits.size() < i + 1){
            return sign;
        }

        if (digits[i] != other.digits[i]) {
            if (digits[i] > other.digits[i])
            {
                return sign;
            }
            else
            {
                return !sign;
            }
        }
    }
    
    if(digits.size() < other.digits.size()){
        return !sign;
    }

    return false;
}

bool big_real::operator<(const big_real &other) const{
    return !(*this == other || *this > other);
}

big_real big_real::operator-() const {
	big_real res(*this);
	res.sign = (sign + 1) % 2;

	return res;
}

big_real big_real::operator+(const big_real& other) const {
	if (sign == other.sign) {
		vector <int> v1(digits);
		vector <int> v2(other.digits);
		
		int dot1 = dot;
		int dot2 = other.dot;

		while (dot1 != max(dot1, dot2)) {
			v1.insert(v1.begin(), 0);
			++dot1;
		}
		while (dot2 != max(dot1, dot2)) {
			v2.insert(v2.begin(), 0);
			++dot2;
		}

		while (v1.size() != max(v1.size(), v2.size())) {
			v1.push_back(0);
		}

		while (v2.size() != max(v1.size(), v2.size())) {
			v2.push_back(0);
		}

		int len = 1 + max(v1.size(), v2.size());

		big_real res;

		res.sign = sign;
		res.digits = vector<int>(len, 0);

		for (int i = 0; i < max(v1.size(), v2.size()); ++i) {
			res.digits[i + 1] = v1[i] + v2[i];
		}

		for (int i = len - 1; i > 0; --i) {
			res.digits[i - 1] += res.digits[i] / 10;
			res.digits[i] %= 10;
		}

		res.dot = max(dot1, dot2) + 1;
		res.remove_extra_zeroes();

		return res;
	}

	if (!sign) {
		return other - (-(*this));
	}
	
	return *this - (-other);
}

big_real big_real::operator-(const big_real& other) const {
	if (sign == 1 && other.sign == 1) {
		vector<int> v1(*this > other ? digits : other.digits);
		vector<int> v2(*this > other ? other.digits : digits);

		int dot1 = *this > other ? dot : other.dot;
		int dot2 = *this > other ? other.dot : dot;

		while (dot1 != max(dot1, dot2)) {
			v1.insert(v1.begin(), 0);
			++dot1;
		}
		while (dot2 != max(dot1, dot2)) {
			v2.insert(v2.begin(), 0);
			++dot2;
		}

		while (v1.size() != max(v1.size(), v2.size())) {
			v1.push_back(0);
		}
		while (v2.size() != max(v1.size(), v2.size())) {
			v2.push_back(0);
		}

		int len = 1 + max(v1.size(), v2.size());

		big_real res;

		res.sign = *this > other ? 1 : 0;
		res.digits = vector<int>(len, 0);

		for (int i = 0; i < max(v1.size(), v2.size()); ++i) {
			res.digits[i + 1] = v1[i] - v2[i];
		}

		for (int i = len - 1; i > 0; --i) {
			if (res.digits[i] < 0) {
				res.digits[i] += 10;
				res.digits[i - 1]--;
			}
		}

		res.dot = max(dot1, dot2) + 1;
		res.remove_extra_zeroes();

		return res;
	}

	if (!sign && !other.sign) {
		return (-other) - (-(*this));
	}
	
	return *this + (-other);
}

big_real big_real::operator*(const big_real& other) const {
	big_real res;

	int len = digits.size() + other.digits.size();

	if(sign == other.sign) {
		res.sign = 1;
	}
	else {
		res.sign = 0;
	}
	res.digits = vector<int>(len, 0);
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

	res.remove_extra_zeroes();

	return res;
}

big_real big_real::operator/(const big_real& other) const {
	
	big_real res = *this * other.inverse();

	int before_dot = max(int(0), dot);

	if (before_dot > res.digits.size() - 1) {
		return res;
	}

	int i = res.digits.size() - 1 - before_dot;
	int t = max(0, res.dot);

	if (i > t && res.digits[i] == 9) {
		while (i > t && res.digits[i] == 9) {
			--i;
		}

		if (res.digits[i] == 9) {
			res.digits.erase(res.digits.begin() + t, res.digits.end());
			if(res.sign) {
				res = res + big_real(1);
			}
			else {
				res = res - big_real(1);
			}
		}
		else {
			res.digits.erase(res.digits.begin() + i + 1, res.digits.end());
			++res.digits[i];
		}
	}

	return res;
}

big_real big_real::inverse() const {
	if (isZero()) {
		throw string("big_real big_real::inverse() - you can't divide by zero!");
	}

	big_real t(*this);
	t.sign = 1;

	big_real one("1");

	big_real res;
	res.sign = sign;
	res.dot = 1;
	res.digits = vector<int>();

	while (t < big_real(1)) {
		t.dot++;
		++res.dot;
	}

	while (one < t) {
		one.dot++;
	}	
	
	res.dot -= one.dot - 1;

	int numbers = 0;
	int before_dot = max(0, res.dot);
	int max_numbers = DivDigits + before_dot;

	do {
		int div = 0;

		while (one > t || one == t) {
			++div;
			one = one - t;
		}

		++one.dot;
		one.remove_extra_zeroes();

		res.digits.push_back(div);
		numbers++;
	} while (!one.isZero() && numbers < max_numbers);

	return res;
}

bool big_real::isZero() const {
	return digits.size() == 1 && digits[0] == 0;
}
