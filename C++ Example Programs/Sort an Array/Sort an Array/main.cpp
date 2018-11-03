//Sort an Array

#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int nums[10]; //Create an array of size 10
    int a, b, t;
    int size;
    
    size = 10; //Number of elements to sort
    
    //Give the array some random values
    for(t=0; t<size; t++) nums[t] = rand();
    
    //Display the original array
    cout << "The Original Array is:\n  ";
    for(t=0; t<size; t++) cout << nums[t] << ' ';
    cout << '\n';
    
    //Sort the Array
    for(a=1; a<size; a++)
        for(b=size-1; b>=a; b--) {
            if(nums[b-1] > nums[b]) { //if the elements are out of order
                //exchange elements
                t = nums[b-1];
                nums[b-1] = nums[b];
                nums[b] = t;
        }
        }
    
    //Display the sorted Array
    cout << "\nThe Sorted Array is:\n ";
    for(t=0; t<size; t++) cout << nums[t] << ' ';
    
    getchar();
    getchar();
    return 0;
    
}
