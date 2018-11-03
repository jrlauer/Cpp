//Function with more than one argument
//Power Function

#include <iostream>
using namespace std;

void power(int base, int exp);

int main() {
    power(10, 2);
    power(10, -2);
    getchar();
    getchar();
    return 0;
}

//Raise an integer to a positive power

void power(int base, int exp) {
    int i;
    
    if (exp < 0) return; //Can't do negative exponents
    
    i = 1;
    
    for( ; exp; exp--) i = base * i;
    cout << "The answer is: " << i;
}
