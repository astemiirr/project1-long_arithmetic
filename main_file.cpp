#include <iostream>
#include <string>

#include <functional>
//#include <utility>

using namespace std;

string str_sum(string x, string y){
	
	if(y.length() > x.length()){
		exchange(x, y);
	}
	
	int next_pos = 0;
	for(int i = x.length() - 1, j = y.length() - 1; i >= 0; --i, --j){
		if(j >= 0){
			char t = (x[i] - '0' + y[j] - '0' + next_pos) % 10 + '0';
			next_pos = (x[i] - '0' + y[j] - '0' + next_pos) / 10;
			x[i] = t; 
		}
		else{
			char t = (x[i] - '0' + next_pos) % 10 + '0';
			next_pos = (x[i] - '0' + next_pos) / 10;
			x[i] = t; 
		}
		     
	}
	if(next_pos){
		x = char(next_pos + '0') + x;
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

int main(){
    string a, b;
    cout << "write two positive numbers for sum:\n";
    cin >> a >> b;
    string sum = str_sum(a, b);

    cout << "sum = " << sum << "\n\n";
    
    
    cout << "write two positive numbers for difference:\n";
    cin >> a >> b;
    string dif = str_dif(a, b);

    cout << "difference = " << dif << "\n\n";  

    //cout
    return 0;
}