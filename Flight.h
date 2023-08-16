#include <array>
#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <cstring>
#include <vector>
// #include "User.h"
using namespace std;

#ifndef FLIGHT_H
#define FLIGHT_H

class Passenger;
class User;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Flight Class

class Flight{
protected: //declaring public variables
    int flightNumber;
    string origin;
    string destination;
    int year;
    int month;
    int day;
    int hour;
    int min;
    double duration;
    int maxSeats;
    int numSeats;
    int availableSeats;
    string mealPreference;
    double price;
    string status = "Economy";
    
    vector <Passenger> flightPassengers; //creating a vector of type Passengers to store all the passengers of a particular flight
public:
    
    //flight constructor - takes in these parameters and assigns them to the variables
    Flight(){}
    Flight(string depCity, string arrCity, int day, int month, int year, int hour, int minute, double length, int seats, int number, double Price)
        : origin(depCity), destination(arrCity), day(day), month(month), year(year), hour(hour), min(minute), duration(length), maxSeats(seats), flightNumber(number), price(Price) {
            availableSeats = maxSeats;
            numSeats = 0;
            mealPreference = "";
        }


    //getter function for Flight Number
    int getFlightNumber(){  return flightNumber;}

    int getYear(){  return year;}

    int getMonth(){  return month;}

    int getDay(){  return day;}

    int getHour(){  return hour;}

    int getMin(){  return min;}

    int getBookedSeats(){ return numSeats;}

    string getOrigin(){  return origin;}

    string getDestination(){  return destination;}

    virtual vector<Passenger> getPassengerList(){
        return flightPassengers;
    }

    // Method to add a passenger to the flight
       bool addPassengers(User* loggedInUser, Flight flight);
    
    void setSeat(int seat){
        numSeats = seat;
    }

    virtual string getStatus(){
        return status;
    }

//virtual function so it can be overriden by derived class
    virtual double getTicketPrice(){
        return price;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//derived class of Flight
class BusinessClass : public Flight {
private:
    string status = "Business";
    double businessPriceMultiplier=1.5;
    string mealPreference;
    vector <Passenger> businessPassengers; //passenger list for business class flights

public:
    BusinessClass(string depCity, string arrCity, int day, int month, int year, int hour, int minute, double length, const int maxSeats, int number, double price, double businessPriceMultiplier)
        : Flight(depCity, arrCity, day, month, year, hour, minute, length, maxSeats, number, price), businessPriceMultiplier(businessPriceMultiplier) {}

    // Getter functions
    double getBusinessPriceMultiplier() const { return businessPriceMultiplier; }
    
    double getTicketPrice(){
            return (price*businessPriceMultiplier);
        }

    // Setter functions
    void setBusinessPriceMultiplier(double multiplier) { businessPriceMultiplier = multiplier; }
    
    vector<Passenger> getPassengerList(){
     return businessPassengers;
    }
    
    string getStatus(){ //returns a different status than the base Flight class
        return status;
    }

    //
    void setMeal(){
        system("clear");
        cout << "Choose your meal preference as a NUMERICAL value:" << endl << endl;
        cout << "(1) Vegetarian" << endl;
        cout << "(2) Pescatarian" << endl;
        cout << "(3) Vegan" << endl;
        cout << "(4) Meat-eater" << endl;
    int choice;
    cin >> choice;
        if(choice==1){
            mealPreference = "Vegetarian";
        }
        else if(choice==2){
            mealPreference = "Pescatarian";
        }
        else if(choice==3){
            mealPreference = "Vegan";
        }
        else if(choice==4){
            mealPreference = "Meat-eater";
        }
    }

    
};


#endif