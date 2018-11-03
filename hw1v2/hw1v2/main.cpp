//John Lauer - CIS 554

//HW1  Polynomial Operations using linked lists

//Due 11:59 pm, February 2 (Friday)
//
//A polynomial is implemented using a linked list.  Only non-zero coefficients are included in linked list.
//Implment member functions operator+ , operator* , and add term
//
//You have to use the main function and print_linked_list provided to you.

#include <iostream>

using namespace std;

class term {
public:
    int power;
    int coef;
    term * next;
    term() { next = nullptr; }
    term(int c, int p) { power = p; coef = c; next = nullptr; }
};

class polynomial {
public:
    int num_terms;
    term * head;
    polynomial() { num_terms = 0; head = nullptr; }
    
    void add_term(int c, int p);
    //If the polynomial does not contain a term with power p,
    //then add this new term.
    //If the polynomial contains a term with power p,
    //then add c to the existing coef.
    
    polynomial operator+(polynomial P);
    polynomial operator*(polynomial P);
    void print_polynomial();
};


void polynomial::print_polynomial() {
    cout << endl;
    term * p = head;
    while (p != nullptr) {
        cout << p->coef << " " << p->power << "   ";
        p = p->next;
    }
}

void polynomial::add_term(int c, int p) {
    term *p = new term(c, p);
    if ((head == nullptr) || (p > head -> power)){
        *p -> next = head;
        head = *p;
        num_terms++;
    }
    if (p == head->power) {
        if (c + head -> coef != 0) {
            head -> coef += c; delete; return;
        }
    } else {
        term * p1 = head;
        p2 = p1 -> next;
    }
    while ((p2 != nullptr) && p < p2 -> power)) {
        p1 = p2;
        p2 = p2 -> next;
    }
}

polynomial polynomial::operator+(polynomial P) {
    //Add terms with same p
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->power == p2->power) {
            p1->coef = (p1->coef) + (p2->coef);
            p2->coef = 0;
        }
    }
    return *this;
}

polynomial polynomial::operator*(polynomial P) {
    //Multiply each term of polynomial with each term of second polynomial
    while(p1 != nullptr) {
        while (p2 != nullptr) {
            p1->power * p2->power;
            p1->coef * p2->coef;
            p2 = p2 -> next;
        }
        p2 = p2 -> head;
        p1 = p1 -> next;
    }
    return *this;
}


int main() {
    polynomial p1, p2, p3, p4, p5, p6;
    int num_t;
    cout << "Enter numer of terms" << endl;
    cin >> num_t;
    cout << "Enter all terms" << endl;
    for (int i = 0; i < num_t; i++) { //You don't need to check for input error
        int c, p;
        cin >> c >> p;
        p1.add_term(c, p);
    }
    p1.print_polynomial();
    cout << endl;
    cout << "Enter numer of terms" << endl;
    cin >> num_t;
    cout << "Enter all terms" << endl;
    for (int i = 0; i < num_t; i++) { //You don't need to check for input error
        int c, p;
        cin >> c >> p;
        p2.add_term(c, p);
    }
    p2.print_polynomial();
    p3 = p1 + p2;
    p3.print_polynomial();
    p4 = p1 * p2;
    p4.print_polynomial();
    getchar();
    getchar();
    return 0;
}
/*
 //An example screenshot is given below:
 //Different cases may be used during grading
 
 Enter numer of terms
 3
 Enter all terms
 2 2 1 1 4 0
 
 2 2   1 1   4 0
 Enter numer of terms
 2
 Enter all terms
 -6 1 3 0
 
 -6 1   3 0
 2 2   -5 1   7 0
 -12 3   -21 1   12 0
