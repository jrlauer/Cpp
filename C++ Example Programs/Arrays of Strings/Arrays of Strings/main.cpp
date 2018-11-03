//A simple computerized telephone directory
//Example of array of strings

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int i;
    char str[80];
    char numbers[10][80] = { //An array of 10 strings, each capable of holding up to 79 characters
        "Tom", "555-3322",
        "Mary", "555-8976",
        "Jon", "555-1037",
        "Rachel", "555-1400",
        "Sherry", "555-8873"
    };
    
    cout << "Enter name: ";
    cin >> str;
    
    for(i=0; i<10; i += 2)
        if(!strcmp(str, numbers[i])) { //If the two strings are equal
            cout << "Number is: " <<numbers[i+1] << "\n";
        }
    
    if (i==10) cout << "Not found.\n";
    
    getchar();
    getchar();
    return 0;
}
