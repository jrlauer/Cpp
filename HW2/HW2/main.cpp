//John Lauer
//HW2
//Implement the three member functions of linked_list class: reverse, sort, remove_all, and insert
//as described in the code below
//Due: 11:59pm, Thursday, February 15

#include <iostream>
using namespace std;

class node {
public:
    int value;
    node * next;
    node * previous;
    node() { next = previous = nullptr; }
    node(int k) { value = k; next = previous = nullptr; }
};

class linked_list {
public:
    node * head;
    node * tail;
    linked_list() {head = tail = nullptr; }
    void make_random_list(int k, int m);//create a linked list of
    //k nodes with values in 0 ..m-1 randomly
    void print_forward(); //Print values of all nodes from head node
    void print_reverse(); //Print values of all nodes reversely from tail node
    void reverse(); //Reverse the order of nodes of linked list
    void sort(); //Sort the nodes, based on ascending order of node values
    
    void insert(int k); //Create a new node with values k, and properly add it to an already sorted list
    //After the insertion, the entire linked list is still sorted.
    //You are not allowed to invoke the function sort()
    
    void remove_all(int k); //Remove all nodes whose node values are equal to k
    
};
void linked_list::make_random_list(int k, int m) { //create linked list of k nodes with
    //values randomly in 0 ... m-1
    node * p;
    for (int i = 0; i < k; i++) {
        p = new node(rand() % m);
        p->next = head;
        if (head == nullptr) {
            tail = p; head = p;
        }
        else {
            head->previous = p;
            head = p;
        }
    }
}

void linked_list::print_forward() {
    node * p = head;
    cout << endl;
    while (p != nullptr) {
        cout << p->value << " ";
        p = p->next;
    }
}

void linked_list::print_reverse() {
    node * p = tail;
    cout << endl;
    while (p != nullptr) {
        cout << p->value << " ";
        p = p->previous;
    }
}

void linked_list::reverse() {
    if (head == nullptr) return;
    node * p1 = head, * p2;
    while (p1 != nullptr) {         //Reverse nodes and then swap head and tail
        p2 = p1->next;
        p1->next = p1->previous;
        p1->previous = p2;
        p1 = p2;
    }
    p2 = head;
    head = tail;
    tail = p2;
}


void linked_list::sort(){
    if (head == nullptr || head->next == nullptr) return;
    node * currNode, * prevNode, * nNode, * p4 = nullptr, *temp; //P1 = current node, P2 = previous node, P3 = next node, P4 = end node (node after tail)
    while (p4 != head->next) {
        prevNode = currNode = head;
        nNode = currNode->next;
        while(currNode != p4) {                   //While current node is not equal to the end node
            if(currNode->value > nNode->value){      //If the current node's value is less than the next node's value
                if(currNode == head) {            //If the head node needs to be switched
                    temp = nNode->next;
                    temp->previous = currNode;
                    nNode->next = currNode;
                    nNode->previous = nullptr;
                    currNode->next = temp;
                    currNode->previous = nNode;
                    head = nNode;
                    prevNode = nNode;
                }else if(nNode == tail) {     //If the tail node needs to be switched
                    nNode->next = currNode;
                    nNode->previous = prevNode;
                    prevNode->next = nNode;
                    currNode->next = nullptr;
                    currNode->previous = nNode;
                    tail = currNode;
                    prevNode = nNode;
                    nNode = currNode->next;
                } else {                   //If a node in the middle of the linked list needs to be switched
                    temp = nNode->next;
                    temp->previous = currNode;
                    nNode->next = currNode;
                    nNode->previous = prevNode;
                    currNode->next = temp;
                    currNode->previous = nNode;
                    prevNode->next = nNode;
                    prevNode = nNode;
                }
                }else{                    //If the current node doesn't need to be switched, go to the next node
                    prevNode = currNode;
                    currNode = currNode->next;
                }
                nNode = currNode->next;
                if(nNode == p4) {            //If the next node is equal to the end node, put the new node at the end of the linked list
                    p4 = currNode;
                }
        }
    }
    
}
void linked_list::insert(int k){
    node * p1 = head, * p2, * p3; //p1 = current node, p2 = previous node, p3 = next node
    node * p4 = new node(k);      //New node to be inserted
    bool insert = false;
    
    p2 = p1 = head;
    p3 = p1->next;
    while(!(insert) && p1 != nullptr){  //While the new node hasn't been inserted and there are values
        if(p4->value <= p1->value){
            if(p1 == head) {            //If our current head is equal to the head
                p4->next = p1;
                p1->previous = p4;
                head = p4;              //Set the new node as the head
            }else{
                p2->next = p4;          //Set previous's next as new node
                p4->previous = p2;      //Set new node's previous as previous
                p4->next = p1;          //Set new node's next and current
                p1->previous = p4;      //Set currents node's previous as new node
            }
            insert = true;              //Set to true because the node was inserted
        }else if(p4->value > p1->value && p3 == nullptr){   //If the new nodes value is greater than the current value
            p1->next = p4;          //Set current node's next as new node
            p4->previous = p1;      //Set new node's previous as current node
            tail = p4;              //Set tail as new node
            insert = true;          //Set insert to true beacuse we have inserted the new node
        }else{                      //In case we didn't find it move on to the next node
            p2 = p1;
            p1 = p1->next;
            p3 = p1->next;
        }
    }
}

void linked_list::remove_all(int k){
    if (head == nullptr) return;
    node * p1 = head, *p2;
    while (p1 != nullptr) {
        p2 = p1->next;
        if (p1->value == k) {                                               //If the node's value is equal to the value you want to remove
            if (p1 == head) head = p1->next;
            if (p1 == tail) tail = p1->previous;
            if (p1->next != nullptr) {p1->next->previous = p1->previous;}
            if (p1->previous != nullptr) {p1->previous->next = p1->next;}
            delete p1;
        }
        p1 = p2;
    }
}
int main() {
    
    linked_list L1;
    L1.make_random_list(60, 15);
    L1.print_forward();
    L1.print_reverse();
    L1.reverse();
    L1.print_forward();
    L1.print_reverse();
    L1.remove_all(11);
    L1.print_forward();
    L1.print_reverse();
    L1.sort();
    L1.print_forward();
    L1.print_reverse();
    L1.insert(0);
    L1.insert(10);
    L1.insert(16);
    L1.print_forward();
    L1.print_reverse();
    getchar();
    getchar();
    return 0;
}
