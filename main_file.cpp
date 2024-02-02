#include <iostream>
#include <vector>
#include <string>
//#define DEBUG
//#include <functional>
//#include <utility>

using namespace std;

string str_sum(string x, int px, string y, int py){
	
	if(py > px){
		swap(x, y);
		swap(px, py);
	}
	while(x.length() - px > y.length() - py){
		x += "0";
	}
	
	int next_pos = 0;
	for(int i = x.length() - 1, j = y.length() - 1; i >= 0; --i, --j){
		if(j >= 0){
			const char t = (x[i] - '0' + y[j] - '0' + next_pos) % 10 + '0';
			next_pos = (x[i] - '0' + y[j] - '0' + next_pos) / 10;
			x[i] = t;
		}
		else{
			const char t = (x[i] - '0' + next_pos) % 10 + '0';
			next_pos = (x[i] - '0' + next_pos) / 10;
			x[i] = t; 
		}
		     
	}
	if(next_pos){
		string x1 = "";
		x1 += char(next_pos + '0');
		x1 += x;
		x = x1;
	}
	
	if(px < x.length()){
		x = x.substr(0, px) + "." + x.substr(px);
	}
	return x;
}

string str_dif(string x, string y){
	
	if(y.length() > x.length()){
		exchange(x, y);
	}
	
	for(int i = x.length() - 1, j = y.length() - 1; i >= 0; --i, --j){
		if(j >= 0){
			if(x[i] - y[j] >= 0){
				x[i] = (x[i] - y[j] + '0');
			}
			else{
				x[i] += 10;
				int ind = i - 1;
				while(!(x[ind] - '0')){
					x[ind] += 9;
					--ind;
				}
				--x[ind];
				
				x[i] = (x[i] - y[j] + '0');
			}
		}
	}
	
	int i = 0;
	while(!(x[i] - '0')){
		++i;
	}
	string x1 = "";
	for(; i < x.length(); ++i){
		x1 += x[i];
	}
	
	return x1;
}

//-----------------------------------------------------------

class big_int
{
	private:
		string digits; //?????
		bool is_negative;
		int point_pos;
		
	public:
		big_int()
		{
			digits = "0";
			is_negative = 0;
			point_pos = digits.length();
		}
		big_int(const string big_str)
		{
			#ifdef DEBUG
			cout << "constructor big_int(string big_str)\n";
			#endif
			
			digits = big_str; //?
			is_negative = 0;
			point_pos = digits.length();
			
			if(digits[0] == '-'){
				is_negative = 1;
				digits.erase(0, 1);
			}
			
			for(int i=digits.length(); i>=0; --i){
				if(digits[i] == '.'){
					point_pos = i;
					digits.erase(i, 1);
					break;
				}
			}
			
			#ifdef DEBUG
			cout << "out constructor big_int(string big_str)\n";
			#endif
		}
		big_int(const long long big_str)
		{
			#ifdef DEBUG
			cout << "constructor big_int(long long big_str)\n";
			#endif
		
			digits = to_string(big_str); //?
			is_negative = 0;
			point_pos = digits.length();
			
			if(digits[0] == '-'){
				is_negative = 1;
				digits.erase(0, 1);
			}
			
			for(int i=digits.length(); i>=0; --i){
				if(digits[i] == '.'){
					point_pos = i;
					digits.erase(i, 1);
					break;
				}
			}
			
			#ifdef DEBUG
			cout << "out constructor big_int(long long big_str)\n";
			#endif
		}
		
		void operator=(const big_int &other){
			digits = other.digits;
			is_negative = other.is_negative;
			point_pos = other.point_pos;
		}
		
		big_int operator+(const big_int &other){
			//if()
			string str_res = str_sum(digits, point_pos, other.digits, other.point_pos);
			big_int result(str_res);
			if(is_negative && other.is_negative){
				result.is_negative = 1;
			}
			return result;
		}
		
		/*big_int operator-(const big_int &other){
			if(!is_negative && other.is_negative){
				big_int
				return (*this + other); //?????
			}
			string str_res = str_dif(digits, point_pos, other.digits, other.point_pos);
			big_int result(str_res);
			if(is_negative && other.is_negative){
				result.is_negative = 1;
			}
			return result;
		}*/
		
		void print(){
			if(is_negative){
				cout << "-";
			}
			cout << digits.substr(0, point_pos);
			if(point_pos < digits.length()){
				cout << ".";
			}
			if(point_pos < digits.length()){
				cout << digits.substr(point_pos);
			}
		}
};

int main(){
	string s1, s2;
	cin >> s1 >> s2;
	big_int a(s1), b(s2);
	cout<< "a: "; a.print(); cout << endl;
	cout<< "b: "; b.print(); cout << endl;
	big_int c;
	c = a + b;
	cout<< "c = a + b: "; c.print(); cout << " vot\n";
	
	/*big_int d;
	d = a - b;
	cout<< "d = a - b: "; d.print(); cout << " vot\n";*/
	
    return 0;
}
