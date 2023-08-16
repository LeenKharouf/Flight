#include <array>
#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <cstring>
#include <vector>
#include <fstream>
#include "Flight.h"

using namespace std;

#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger{
    friend class User; //so User can access its private/protected variables

protected:
    string firstName;
    string lastName;
    string passport;
    int seatNumber;
    vector <Flight> flightsBooked; //creates a vector of type Flight to store flightsBooked by passenger
    
public:
    
    Passenger(){}//default constructor
    
    //setters
    void setFirstName(string first){firstName = first;}
    
    void setLastName(string last){lastName = last;}
    
    void setPassport(string Passport){passport = Passport;}
    
    //getters
    
    string getFirstName(){return firstName;}
    
    string getLastName(){return lastName;}
    
    string getPassport(){return passport;}
    
    vector <Flight> getFlightsBooked(){
        return flightsBooked;
    }
    
    //setting passenger information
    void setPassengerDetails(int seats, Flight flight) { 
        seatNumber = seats+1;
        cout << "Enter First Name: " << endl;
        cin >> firstName;
        cout << "Enter Last Name: " << endl;
        cin >> lastName;
        cout << "Enter Passport Number: " << endl;
        cin >> passport;
    }

    //adds flight to flightsBooked vector
     void addFlightBooked(Flight flight) {
        flightsBooked.push_back(flight);
    }

    //prints details on screen
    void printPassengerDetails(){
            cout << "-------------------------------------------------------------------------" <<endl;

            cout << "\nPassenger Details: " << endl<<endl;
            cout << "Name: " << getFirstName() << " " << getLastName() << endl<<endl;
            cout << "Flight Booked: ";
            for (int i = 0; i < flightsBooked.size(); i++) {
                cout << "Flight Number " << flightsBooked[i].getFlightNumber() << " going from " << flightsBooked[i].getOrigin() << " to " << flightsBooked[i].getDestination() <<endl<<endl;
                cout << "Class: " << flightsBooked[i].getStatus() << endl<<endl;
                if(flightsBooked[i].getStatus() == "Business"){
                    cout << "PREMIUM MEAL" << endl<<endl; 
                }
            }
            
            cout << "Seat Number: " << seatNumber << endl<<endl; 
            cout << "-------------------------------------------------------------------------" <<endl;
            cout << "-------------------------------------------------------------------------" <<endl;

        }
    
    //prints the tickets in a .txt file
    void printTicket(int num){
            int myPassengers = num;
          // create output write object
           string document = getLastName() + "_" + getFirstName() + "_Ticket" + to_string(num) + ".txt";            
            ofstream outfile;

            for (int i = 0; i < flightsBooked.size(); i++) {
                // open file for writing
                outfile.open(document);

                // write to file
                outfile << "-------------------------------------------------------------------------" <<endl;
                outfile << "-------------------------------------------------------------------------" <<endl;

                outfile << "\nPassenger Details: " << endl<<endl;
                outfile << "Name: " << getFirstName() << " " << getLastName() << endl<<endl;
                outfile << "Flight Booked: ";
                outfile << "Flight Number " << flightsBooked[i].getFlightNumber() << " going from " << flightsBooked[i].getOrigin() << " to " << flightsBooked[i].getDestination() <<endl<<endl;
                outfile << "Class: " << flightsBooked[i].getStatus() << endl<<endl;
                
                if(flightsBooked[i].getStatus() == "Business"){ //if its a business flight, you get a free meal 
                    outfile << "PREMIUM MEAL" << endl<<endl; 
                }
            }
            
            outfile << "Seat Number: " << seatNumber << endl<<endl; 
            outfile << "-------------------------------------------------------------------------" <<endl;
            outfile << "-------------------------------------------------------------------------" <<endl;
            
            // close the file.
            outfile.close();
    }
        
   
};

#endif