//Standard Template library (STL)
//vector, list, map -- collections

#include <iostream>
#include <vector> //array
#include <list> //linked list
#include <map> //association relationship


using namespace std;

int main() {
    vector<int> V1 = { 0, 1, 2, 3 ,4 };
    for (int i = 0; i < V1.size(); i++) {
        cout << V1[i];
    }
    
    V1.push_back(5);
    V1.pop_back();
    for (int i = 0; i < V1.size(); i++) {
        cout << V1[i];
    }
    list<int> L1 = { 0, 1, 2, 3 ,4 };
    L1.push_back(5);
    L1.pop_back();
    L1.push_front(-1);
    L1.pop_front();
    
    getchar();
    getchar();
    return 0;
}

