//Functions with Recursion
//Print a string backwards

#include <iostream>
using namespace std;

void reverse(char *s);

int main() {
    char str[] = "this is a test";  //Create a String
    
    reverse(str);                   //Call Reverse Function
    getchar();
    getchar();
    return 0;
}
//Function to Print string backwards
void reverse(char *s) {
    if(*s)
        reverse(s+1);
    else
        return;
    
    cout << *s;
}
