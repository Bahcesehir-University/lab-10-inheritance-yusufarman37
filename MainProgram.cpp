// ================================================================
// Lab: Inheritance in C++
// Course: Object-Oriented Programming for Engineers
// File: MainProgram.cpp
// ================================================================
// INSTRUCTIONS:
//   Complete every TODO. Do NOT change function signatures.
//   All code stays in this single file. No .h files allowed.
// ================================================================
#include <iostream>
#include <string>
#include <sstream>
// ================================================================
// CLASS DEFINITIONS
// ================================================================
// ----------------------------------------------------------------
// Base Class: Vehicle
// ----------------------------------------------------------------
// Represents a generic vehicle.
// Data members (protected):
//   - make       (std::string)  : e.g. "Toyota"
//   - year       (int)          : e.g. 2020
//   - fuelLevel  (double)       : 0.0 - 100.0 (percentage)
//
// Methods:
//   - Constructor(make, year, fuelLevel)
//   - getMake()       -> std::string  (const)
//   - getYear()       -> int          (const)
//   - getFuelLevel()  -> double       (const)
//   - refuel(amount)  -> void         : adds amount to fuelLevel,
//                                       clamps max to 100.0
//   - describe()      -> std::string  : pure virtual
//   - virtual destructor
// ----------------------------------------------------------------
class Vehicle {
protected:
   std::string make;
   int year;
   double fuelLevel;
public:
   Vehicle(std::string make, int year, double fuelLevel);
   std::string getMake() const;
   int getYear() const;
   double getFuelLevel() const;
   void refuel(double amount);
   virtual std::string describe() const = 0;
   virtual ~Vehicle() {}
};
// ----------------------------------------------------------------
// Derived Class: Car
// ----------------------------------------------------------------
// Inherits from Vehicle.
// Additional data (private):
//   - numDoors (int)
//
// Methods:
//   - Constructor(make, year, fuelLevel, numDoors)
//     -> must call Vehicle constructor
//   - getNumDoors() -> int (const)
//   - describe()    -> std::string (override)
//     Format: "Car: <make> (<year>), <numDoors> doors, fuel: <fuelLevel>%"
//     Example: "Car: Toyota (2020), 4 doors, fuel: 75.5%"
// ----------------------------------------------------------------
class Car : public Vehicle {
private:
   int numDoors;
public:
   Car(std::string make, int year, double fuelLevel, int numDoors);
   int getNumDoors() const;
   std::string describe() const override;
};
// ----------------------------------------------------------------
// Derived Class: Truck
// ----------------------------------------------------------------
// Inherits from Vehicle.
// Additional data (private):
//   - payloadTons (double)   : cargo capacity in tons
//
// Methods:
//   - Constructor(make, year, fuelLevel, payloadTons)
//     -> must call Vehicle constructor
//   - getPayloadTons() -> double (const)
//   - describe()       -> std::string (override)
//     Format: "Truck: <make> (<year>), payload: <payloadTons>t, fuel: <fuelLevel>%"
//     Example: "Truck: Ford (2018), payload: 5.5t, fuel: 60%"
// ----------------------------------------------------------------
class Truck : public Vehicle {
private:
   double payloadTons;
public:
   Truck(std::string make, int year, double fuelLevel, double payloadTons);
   double getPayloadTons() const;
   std::string describe() const override;
};
// ================================================================
// FUNCTION IMPLEMENTATIONS
// ================================================================
// ----------------------------------------------------------------
// Vehicle member function implementations
// ----------------------------------------------------------------
Vehicle::Vehicle(std::string make, int year, double fuelLevel)
   : make(make), year(year), fuelLevel(fuelLevel) {}
std::string Vehicle::getMake() const {
   return make;
}
int Vehicle::getYear() const {
   return year;
}
double Vehicle::getFuelLevel() const {
   return fuelLevel;
}
void Vehicle::refuel(double amount) {
   if (amount <= 0) {
       return;
   }
   fuelLevel += amount;
   if (fuelLevel > 100.0) {
       fuelLevel = 100.0;
   }
}
// ----------------------------------------------------------------
// Car member function implementations
// ----------------------------------------------------------------
Car::Car(std::string make, int year, double fuelLevel, int numDoors)
   : Vehicle(make, year, fuelLevel), numDoors(numDoors) {}
int Car::getNumDoors() const {
   return numDoors;
}
std::string Car::describe() const {
   std::ostringstream oss;
   oss << "Car: " << make << " (" << year << "), "
<< numDoors << " doors, fuel: " << fuelLevel << "%";
   return oss.str();
}
// ----------------------------------------------------------------
// Truck member function implementations
// ----------------------------------------------------------------
Truck::Truck(std::string make, int year, double fuelLevel, double payloadTons)
   : Vehicle(make, year, fuelLevel), payloadTons(payloadTons) {}
double Truck::getPayloadTons() const {
   return payloadTons;
}
std::string Truck::describe() const {
   std::ostringstream oss;
   oss << "Truck: " << make << " (" << year << "), payload: "
<< payloadTons << "t, fuel: " << fuelLevel << "%";
   return oss.str()
}
// ================================================================
// MAIN
// ================================================================
int main() {
   // --- Basic usage demo ---
   Car   c("Toyota", 2020, 75.5, 4);
   Truck t("Ford",   2018, 60.0, 5.5);
   std::cout << c.describe() << "\n";
   std::cout << t.describe() << "\n";
   // Polymorphism via base pointer
   Vehicle* v1 = &c;
   Vehicle* v2 = &t;
   std::cout << v1->describe() << "\n";
   std::cout << v2->describe() << "\n";
   // Refuel demo
   c.refuel(20.0);
   std::cout << "After refuel: " << c.getFuelLevel() << "%\n";
   return 0;
}
