//Object Pointer

#include <iostream>
using namespace std;

class P_example {
    int num;
public:
    void set_num(int val) {num = val;}
    void show_num() {cout << num << "\n";}
};

int main() {
    P_example ob, *p; //declare an object and pointer to it
    
    ob.set_num(1); //call functions directly on ob
    ob.show_num();
    
    p = &ob;       //assign p the address of ob
    p->set_num(20);//Call functions through a pointer to ob
    p->show_num();
    
    getchar();
    getchar();
    return 0;
}
