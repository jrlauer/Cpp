//Return a reference through a function

#include <iostream>
using namespace std;

double &f(); // Return a reference to a double

double val = 100.0;

int main() {
    double x;
    
    cout << f() << '\n'; //Display val's value
    
    x = f();             //Assign Value of val to x
    cout << x << '\n';   //Display x's value
    
    f() = 99.1;          //Change val's value. This changes the actual value because f is a reference to val
    cout << f() << '\n'; //Display val's new value
    
    getchar();
    getchar();
    return 0;
}

//This function returns a reference to a double
double &f() {
    return val; //Return reference to val
}
