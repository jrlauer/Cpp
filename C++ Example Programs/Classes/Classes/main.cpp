//Classes and the :: operator
//Calculate miles a car can go with a full tank

#include <iostream>
using namespace std;

//Declare the Vehicle class
class Vehicle {
public:
    int passengers; //Number of passengers
    int fuelcap;    //Fuel capacity in gallons
    int mpg;        //Fuel consumption in miles per gallon
    
    int range();    //Compute and return the range (Declare Range)
};

//Implement the range member function

int Vehicle::range() {      //Implement range()
    return mpg * fuelcap;
}

int main() {
    Vehicle minivan;    //Create a vehicle object
    Vehicle sportscar;  //Create another object
    
    int range1, range2;
    
    //Assign values to fields in minivan
    minivan.passengers = 7;
    minivan.fuelcap = 16;
    minivan.mpg = 21;
    
    //Assign values to fields in sportscar
    sportscar.passengers = 2;
    sportscar.fuelcap = 14;
    sportscar.mpg = 12;
    
    //Compute the ranges assuming a full tank of gas
    range1 = minivan.range();
    range2 = sportscar.range();
    
    cout << "Minivan can carry " << minivan.passengers << " with a range of " << range1 << "\n";
    cout << "Sportscar can carry " << sportscar.passengers << " with a range of " << range2 << "\n";
    
    getchar();
    getchar();
    return 0;
    
}
