//John Lauer
//HW4: Implement a generic bag using template
//Due: April 1 (Sunday) at 11:59pm
//Note that for class linked_list and bag, you need to also include destructor, copy constructor, move constructor, left ref operator=, and right ref operator=

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

template <class T> class ThreeD {
public:
    T ht;
    T wid;
    T dep;
    ThreeD() { ht = wid = dep = 0; }
    ThreeD(T i) { ht = wid = dep = i; }
    ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
    
    template <class B>
    friend ostream & operator<<(ostream &stream, const ThreeD<B> &t); //Enable cout for ThreeD
};
template <class T> class node {
public:
    T value;
    node<T> * next;
    node<T> * previous;
    node<T>() { next = previous = nullptr; }
    node<T>(T v) { value = v; next = previous = nullptr; }
};
template <class T> class linked_list { //doubly linked list as in HW2
public:
    node<T> * head;
    node<T> * tail;
    int numNodes;
    linked_list() {head = tail = nullptr, numNodes = 0;}
    ~linked_list(){                 //Destructor
        node<T> * temp = head;
        while (temp != nullptr)
        {
            delete temp;            //Delete the node and then move the head to next until all nodes have been deleted
            head = head->next;
            temp = head;
        }
        head = tail = nullptr;      //After nodes have been deleted, delete the head and the tail
    }
    linked_list(const linked_list &L) {         // Copy Constructor
        numNodes = L.numNodes;
        head = nullptr;
        for (int i = 0; i < numNodes; i++) {    //Create linked list of the same size
            node<T> * z = new node<T>();
            z->next = head;
            head = z;
        }
        node<T> * z1 = head;                    //Fill linked list with the same values
        node<T> * z2 = L.head;
        for (int b = 0; b < numNodes; b++) {                 //Until you reach the end of the linked list
            z1->value = z2->value;              //Assign same value as in the linked list
            z2 = z2->next;                      //Move to the next node in both linked lists
            z1 = z1->next;
        }
    }
    linked_list(linked_list &&L) { //Move Constructor
        numNodes = L.num_nodes;                //Set to the same size and delete the value
        head = L.head;
        L.head = nullptr;
    }
    void operator=(linked_list &L){                 //Left Reference Operator
        numNodes = L.numNodes;
        for (int a = 0; a < numNodes; a++) {        //Create Linked List as in copy constructor
            node<T> * t = new node<T>();
            t->next = head;
            head = t;
        }
        node<T> * t1 = head;
        node<T> * t2 = L.head;                      //Add values to Linked List as in copy constructor
        for (int b = 0; b < numNodes; b++) {
            t1->value = t2->value;
            t2 = t2->next;
            t1 = t1->next;
        }
        cout << "Leaving Left Reference Operator" << endl; //Allows me to see when left reference is invoked
    }
    
    void operator=(linked_list &&L){              //Right Reference Operator
        numNodes = L.numNodes;                    //Same as move constructor
        head = L.head;
        L.head = nullptr;
        cout << "Leaving Right Reference Operator" << endl; //Allows me to see when right reference is invoked
    }
    void push_front(T t) {              //Function allows new nodes to be added in the front of the list
        node<T> *x = new node<T>(t);    //Create new node
        x->next = head;                 //Place the new node in front of the head
        head = x;                       //Make the new node the head
        numNodes++;                     //Increase the size of the list to account for new node
    }
    template <class B>
    friend ostream & operator<<(ostream &stream, const linked_list<B> &t); //Enable cout for linked list
};

template <class X>
class item {
public:
    X value;
    item<X> *next;
    item<X> *previous;
    item<X>(X v) { value = v; next = nullptr; previous = nullptr; }
};

template <class X>
class bag {
public:
    item<X> *last;
    item<X> *first;
    int num_items;
    int size() { return num_items; }
    bag() { last = nullptr; first = nullptr; num_items = 0; } //default constructor for bag class
    void push_back(X v);  //insert an item with value v to the back of the bag
    void push_front(X v); //insert an item with value v to the front of the bag
    void pop_back(); //delete the last item in the bag
    void pop_front(); //delete the first item in the bag
    X &operator[](int i); //Access bag item with index.
    X front() {  //it returns the value of the first item in the bag.
        //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.
        return first->value;
    }
    X back() { //it returns the value of the last item in the bag
        //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.
        
        return last->value;
    }
    void clear(); //Delete all items in the bag
    item<X> * find(X x);//find returns address of item with value equal to x or nullptr if match not found
    void erase(item<X> * p); //erase the item pointed by p;
    void erase(int i); //erase the item with index equal to i;
    
    ~bag() {                //Deconstructor
        item<X> *b = first;
        while (b != nullptr) {      //Until there are no more items
            delete b;               //Delete the item
            first = first->next;    //set first to the next item
            b = first;              //set our pointer to the new first item
        }
    }
    bag<X> (const bag<X> &L) {      //Copy Constructor
        num_items = L.num_items;
        first = nullptr;
        for (int i = 0; i < num_items; i++) {   //Create a bag with the same number of items
            item<X> *p = new item<X>();
            p->next = first;
            first = p;
        }
        item<X> *a = first;                     //Set the previous values for the new copy constructor
        item<X> *b = first->next;
        a->previous = nullptr;
        while (a != nullptr && b != nullptr) {
            b->previous = a;
            a = b;
            b = b->next;
        }
        a = first;
        b = L.first;
        for(int i = 0; i < num_items; i++) {                //Unil you reach the end of the bag
            a->value = b->value;                            //Copy the values into the new bag
            a = a->next;
            b = b->next;
        }
    }
    bag<X> (bag<X> &&L) {                       //Move Constructor
        num_items = L.num_items;                //Have the same amount of items
        first = L.first;                        //Set the first item as the same as the original bag
        L.first = nullptr;                      //Delete the value
    }
    void operator=(bag<X> &L) {                 //Left Reference Operator
        num_items = L.num_items;                //Same process as copy constructor
        first = nullptr;
        for (int i = 0; i < num_items; i++) {
            item<X> *p = new item<X>();
            p->next = first;
            first = p;
        }
        item<X> *a = first;
        item<X> *b = first->next;
        a->previous = nullptr;
        while (a != nullptr && b != nullptr) {
            b->previous = a;
            a = b;
            b = b->next;
        }
        a = first;
        b = L.first;
        for(int i = 0; i < num_items; i++) {
            a->value = b->value;
            a = a->next;
            b = b->next;
        }
    }
    void operator=(bag<X> &&L) {     //Right reference operator
        num_items = L.num_items;     //Same process as move constructor
        first = L.first;
        L.first = nullptr;
    }
    template <class B>
    friend ostream & operator<<(ostream &stream, const bag<B> & bag1);  //Enable cout for bag1
};
template<class X>
void bag<X>::push_back(X v) {       //Function allows items to be added to the end of the bag
    item<X> *a = new item<X>(v);    //Create new item
    num_items++;                    //Increase size of the bag to account for new item
    if (last == nullptr) {          //If the bag is currently empty
        last = a;                   //Make the new item both the first and last item of the bag (it's the only one)
        first = a;
        return;
    }                               //If that's not the case:
    a->previous = last;
    last->next = a;                 //Add the new item after the last item of the bag
    last = a;                       //Make the newly added item the last item of the bag
    a->next = nullptr;              //Since it's the last item, p->next should point to nothing
}
template<class X>
void bag<X>::push_front(X v) {      //Function allows items to be added to the beginning of the bag
    item<X> *a = new item<X>(v);    //Create new item
    num_items++;                    //Increase the size of the bag to account for the new item
    if (first == nullptr) {         // If the bag is currently empty
        first = a;                  //Make the new item both the first and last item of the bag since it's the only one
        last = a;
        return;
    }                               //If that's not the case:
    a->next = first;                //We are placing the item in the front, so the next item will be first before we redefine the first
    first->previous = a;            //Add the new item to the beginning of the bag
    first = a;                      //Make the newly added item the first item of the bag
    a->previous = nullptr;          //Since it's the first item, there should be nothing before it
}
template<class X>
void bag<X>::pop_back() {           //Function allows last item of the bag to be removed
    if (first == last)return;       //If the bag is empty, just return
    item<X> *p = last;
    last = last->previous;          //Set the last item to the previous item because we are deleting the last item
    last->next = nullptr;           //The next item should now be nullptr because we are removing
    delete p;                       //Delete or "pop" the last item
    num_items--;                    //Reduce the size of the bag to account for the popped item
}
template<class X>
void bag<X>::pop_front() {          //Function allows the first item of the bag to be removed
    if (first == last)return;       //If the bag is empty, just return (nothing to remove)
    item<X> *p = first;
    first = first->next;            //Make the second item the first item because we are about to remove the first item
    first->previous = nullptr;      //Previous should be nullptr because we are removing the first item
    delete p;                       //Delete or "pop" the first item
    num_items--;                    //Reduce the size of the bag to account for the popped item
}
template<class X>
X& bag<X>::operator[](int i) {      //Function allows you to return a specific item (i) in the bag
    item<X> *p = first;
    for (int j = 0; j < i; j++) {   //Keep moving through the bag until you reach the item you want to return
        p = p->next;
    }
    return p->value;                //Return the item
}
template<class X>
void bag<X>::clear() {              //Function allows all items in the bag to be removed
    item<X> *p = first;
    while (p != nullptr) {          //Until all of the items are removed
        p = first->next;            //Move to the next item
        delete first;               //Delete previous or "first" item
        first = p;                  //Make "first" equal the first item of the bag after the deletion
    }
    num_items = 0;                  //Once all items are removed, set bag size to zero
}
template<class X>
item<X> *bag<X>::find(X x){         //Function looks for a specific item and returns the address
    item<X> * p2 = first;
    for (int i = 0; i < num_items; i++) {         //Search the bag for the item
        if (&p2->value == &x){
            return p2;                            //Return address if you find the item
        }
        p2 = p2->next;
    }
    return first;
}
template<class X>
void bag<X>::erase(item<X> * p) {   //Function erases the item pointed by p
    delete p;                       //Delete p
    num_items--;                    //Reduce the number of items in the bag to account for the deletion
    if(p == first)                  //If p was the first item, then make the second item the new first item
        first = p->next;
    if(p == last)                   //If p was the last item, then make the second to last item the new last item
        last = p->previous;
}
template<class X>
void bag<X>::erase(int i) {         //Function erases the item with index equal to i
    num_items--;                    //Reduce the number of items in the bag to account for the deletion
    item<X> * p1 = first;
    if (i == 0) {                   //If the item we want to delete is the first item, we have to make the second item the new first item
        first = p1->next;
        first->previous = nullptr;
        p1->next = nullptr;
        delete p1;                  //Once we do that, we can delete the item
        return;
    }
    for(int a = 0; a <= i; a++){   //Otherwise, move through the bag until we reach the desired index
        if(p1->next == nullptr) break;
        p1 = p1->next;
    }
    delete p1;                     //Once we reach the desired index, delete the item
}
template <class B>
ostream & operator<<(ostream &stream, const ThreeD<B> &t) {         //Function to print out ThreeD (cout ThreeD)
    stream << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
    return stream;
}
template <class T>
ostream & operator<<(ostream &stream, const linked_list<T> &L) {    //Function to print out linked_list (cout linked_list)
    node<T> *p = L.head;
    while (p != nullptr) {
        stream << p->value << " ";
        p = p->next;
    }
    return stream;
}
template <class X>
ostream & operator<<(ostream &stream, const bag<X> & bag1) {        //Function to print out bag1 (cout bag1)
    item<X> *p = bag1.first;
    while (p != nullptr) {
        stream << p->value << " ";
        p = p->next;
    }
    return stream;
}
int main() {
    bag<double> bag_d;
    bag_d.push_back(5.5);
    bag_d.push_back(6.6);
    bag_d.push_front(4.4);
    bag_d.push_front(3.3);
    bag_d.pop_front();
    bag_d.pop_back();
    cout << bag_d << endl;;
    
    
    bag<int> bag_i;
    bag_i.push_back(5);
    bag_i.push_back(6);
    bag_i.push_front(4);
    bag_i.push_front(3);
    bag_i.pop_front();
    bag_i.pop_back();
    cout << bag_i <<endl;
    
    ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
    bag<ThreeD<int>> bag_3D;
    bag_3D.push_back(td5);
    bag_3D.push_back(td6);
    bag_3D.push_front(td4);
    bag_3D.push_front(td3);
    bag_3D.pop_front();
    bag_3D.pop_back();
    cout << bag_3D << endl;;
    cout << bag_3D.front() <<  bag_3D.back();
    cout  << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D[1] = td7;
    cout << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D.clear();
    cout << bag_3D << endl;;
    cout << bag_3D.size() <<endl;
    
    
    linked_list<string>ls_1;
    ls_1.push_front("David");
    ls_1.push_front("John");
    ls_1.push_front("Pat");
    ls_1.push_front("Ben");
    ls_1.push_front("Jeff");
    cout << ls_1 << endl;
    
    linked_list<string>ls_2;
    ls_2.push_front("Wendy");
    ls_2.push_front("Mary");
    ls_2.push_front("Nancy");
    ls_2.push_front("Jennifer");
    cout << ls_2 << endl;
    
    bag<linked_list<string>> bag_string;
    
    bag_string.push_back(ls_1);
    
    bag_string.push_back(ls_2);
    
    cout << bag_string << endl;
    cout << bag_string[1] << endl;
    
    ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
    linked_list<ThreeD<double>> LTD1;
    LTD1.push_front(t10);
    
    LTD1.push_front(t11);
    linked_list<ThreeD<double>> LTD2;
    LTD2.push_front(t13);
    LTD2.push_front(t12);
    LTD2.push_front(t10);
    LTD2.push_front(t11);
    
    bag<linked_list<ThreeD<double> > > BLTD;
    BLTD.push_back(LTD1);
    BLTD.push_back(LTD2);
    cout << BLTD <<endl;
    
    item<linked_list<ThreeD<double>>> * p2;
    
    p2 = BLTD.find(LTD1);
    BLTD.erase(p2);
    cout << BLTD << endl;
    BLTD.push_back(LTD1);
    cout << BLTD << endl;
    BLTD.erase(0);
    cout << BLTD << endl;
    
    getchar();
    getchar();
    return 0;
}

