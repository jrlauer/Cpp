//Example of shift operators

#include <iostream>
using namespace std;

void show_binary(unsigned int u);

int main() {
    int i=1, t;
    
    //Shift Left
    for(t=0; t<8; t++) {
        show_binary(i);
        i = i << 1;         // Left shift i one position
    }
    cout << "\n";
    
    //Shift Right
    for(t=0; t<8; t++) {
        i = i >> 1;         // Right shift i one position
        show_binary(i);
    }
    
    getchar();
    getchar();
    return 0;
    
}

//Display the bits within a byte
void show_binary(unsigned int u) {
    int t;
    for(t = 128; t>0; t=t/2)
        if(u & t) cout << "1 ";
        else cout << "0 ";
    
    cout << "\n";
}
