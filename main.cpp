#include <iostream>
#include <vector>
#include <string>
#include "big_real.hpp"

using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    big_real a(s1), b(s2);

    cout << "a: ";
    a.print();
    cout << endl;
    cout << "b: ";
    b.print();
    cout << endl;

    big_real c;
    c = a + b;
    cout << "c = a + b: ";
    c.print();
    cout << "\n";

    c = a - b;
    cout << "c = a - b: ";
    c.print();
    cout << "\n";

    return 0;
}