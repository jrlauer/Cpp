//An Introduction to Pointers

#include <iostream>
using namespace std;

int main() {
    int total;
    int *ptr;
    int val;
    total = 3200; //Assign 3,200 to total
    ptr = &total; //Get address of total
    val = *ptr; //Get value at that address
    cout<<"The total is: " <<val<<'\n';
    
    getchar();
    getchar();
    return 0;
}
