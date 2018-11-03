//Reverse a String with Pointers

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    
    char str[] = "this is a test"; //Original String
    char *start, *end;             //Start and end pointers
    int len;                       //Length of the string
    char t;                        //Current Character
    
    cout << "Original: " <<str << "\n";
    
    len = strlen(str);
    
    start = str;
    end = &str[len-1];
    
    while(start < end) {
        //Swap chars
        t= *start;
        *start = *end;
        *end = t;
        
        //Advance pointers
        start++;
        end--;
    }
    
    cout << "Reversed: " << str << "\n";
    getchar();
    getchar();
    return 0;
    
}
