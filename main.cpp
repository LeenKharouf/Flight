#include <array>
#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <cstring>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Passenger.h"
#include "Flight.h"
#include <fstream>
// #include "User.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//forward declaration
class Passenger;
class Flight;

// User definition
class User {
private:
    string ID;
    vector<Passenger> myPassengerList; //passenger list to store all passengers created by user

public:
    User(string id){ //constructor
        ID = id;
    }

    void addPassenger(Passenger p) { //function to add passenger to myPassengerList
        myPassengerList.push_back(p);
    } 

    vector<Passenger> getMyPassengers(){ //getter for myPassengerList
      return myPassengerList;
    }

    string getID() { //getter for ID
        return ID;
    }
};

vector<User> userVector; // Vector of users defined globally


User* login(string id) { // returns a pointer to the current user 
    for (int i = 0; i < userVector.size(); i++) {
        if (userVector[i].getID() == id) {
            return &userVector[i];
        }
    }
    return NULL; // User not found
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//global function to create a list of flights with parameters given by user
    vector<Flight>  createFlights(int chosenDay, int chosenMonth, int chosenYear, string from, string to){
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a uniform integer distribution between 250 and 350
    std::uniform_int_distribution<int> dist(250, 350);
    std::uniform_int_distribution<int> num(100000, 999999);

    vector<Flight> flightsList;
    int hour = rand() % 24;
    int min = 30;
    double duration = (rand() % 6 + 1) * 0.5;
    int seats = 10;
    int price = dist(rng); //assigns random number in the range of dist defined above
    int flightNumber = num(rng); //assigns random number in the range of num defined above

  //creating a flight with the exact date, origin and destination desired by user, and adds it to list
    flightsList.push_back(Flight(from, to, chosenDay, chosenMonth, chosenYear, hour, min, duration, seats, flightNumber, price));

    // Generate 10 other random flights with the same origin and destination desired by the user, but not necessarily the same dates
    for (int i = 1; i < 10; i++) {
        // Randomly generate the date in that specified month
        int day = chosenDay + i;
        int month = chosenMonth;
        int year = chosenYear;

        // Randomly generate the flight time and price
        int hour = rand() % 24;
        int min = 30;
        double duration = (rand() % 6 + 1) * 0.5;
        int price = dist(rng); //assigns random number in the range of dist defined above
        int seats = 10;

        // Generate a random flight number
        int flightNumber = num(rng); //creates a flight number of 6 digits

        // Add the flight to the vector
        flightsList.push_back(Flight(from, to, chosenDay, chosenMonth, chosenYear, hour, min, duration, seats, flightNumber, price)); //creates and adds the flights to the list of flight
    }

    return flightsList; //returns the list of flights to be saved
}

//same idea as flightClass but creates a vector of Business class flights
vector<BusinessClass> createBusinessFlights(int chosenDay, int chosenMonth, int chosenYear, string from, string to){
    vector<BusinessClass> businessFlights;
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a uniform integer distribution between 250 and 350
    std::uniform_int_distribution<int> dist(600, 700);
    std::uniform_int_distribution<int> num(1000000, 9999999);

    // Generate 10 other random flights with the same origin and destination desired by the user, but not necessarily the same dates
  
    for (int i = 1; i < 4; i++) {
        // Randomly generate the date in that specified month
        int day = chosenDay + i;
        int month = chosenMonth;
        int year = chosenYear;

        // Randomly generate the flight time and price
        int hour = rand() % 24;
        int min = 30;
        double duration = (rand() % 6 + 1) * 0.5;
        int price = dist(rng);
        int businessPriceMultiplier = 1.75;
        // Generate a random flight number
        int flightNumber = num(rng); //creates a flight number of 6 digits
        int seats = 5;
        // Add the flight to the vector
        businessFlights.push_back(BusinessClass(from, to, chosenDay, chosenMonth, chosenYear, hour, min, duration, seats, flightNumber, price, businessPriceMultiplier)); //creates and adds the flights to the list of flight
        cout << businessFlights[businessFlights.size() - 1].getTicketPrice() << endl;
    }

    return businessFlights; //returns the list of flights to be saved
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//function to print all the flights in the vector that is passed through the function (prints list of flights)
void displayFlights(vector<Flight>& flightsList, vector<BusinessClass>& businessFlights, int chosenDay, int chosenMonth, int chosenYear, string from, string to){
    cout << "-------------------------------------------------------------------------" <<endl;
    cout << "Here is a list of the flights that match your search:" <<endl;
    cout << "-------------------------------------------------------------------------" <<endl;
    for (auto& flight : flightsList) {
            cout << "Flight number: " << flight.getFlightNumber() << " from: " << flight.getOrigin() << " to " << flight.getDestination() 
            << " on "<< flight.getDay() << "/" << flight.getMonth() << "/" << flight.getYear() <<  " at " << flight.getHour() << ":" << flight.getMin() << " | Price = $" << flight.getTicketPrice() << " | Class: " << flight.getStatus()<< endl<<endl;
        }
    for (auto& flight : businessFlights) {
            cout << "Flight number: " << flight.getFlightNumber() << " from: " << flight.getOrigin() << " to " << flight.getDestination() 
            << " on " << flight.getDay() << "/" << flight.getMonth() << "/" << flight.getYear() <<  " at " << flight.getHour() << ":" << flight.getMin() << " | Price = $" << flight.getTicketPrice() << " | Class: " << flight.getStatus()<< endl<<endl;
        }
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//inline function to create a new passenger
 inline Passenger createNewPassenger(int seat, Flight flight) {
            Passenger passenger;
            passenger.setPassengerDetails(seat, flight);
            passenger.printPassengerDetails();
   return passenger;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//function to add a new passenger
bool Flight::addPassengers(User* loggedInUser, Flight flight) { 
    if (numSeats == maxSeats) { //checks if there are available seats
        cout << "Sorry, there are no available seats on this flight." << endl;
        return false;
    } else {
        Passenger p = createNewPassenger(numSeats, flight); //create a passenger in flight 'flight' with seat number 'numSeats'
        numSeats++;
        p.addFlightBooked(flight); //adds flight to vector of flightsBooked
        flightPassengers.push_back(p); //adds passenger to vector of flightPassengers,
        loggedInUser->addPassenger(p); //adds passenger to vector of myPassengerList,
        return true;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
  string exit;
  string choiceMain;
  string choiceBooking;
  string email;


  cout << "\nWelcome to AirLeens, your online Flight Reservation System!\n\n";

    int mainmenu = 1;

    do{
      //Login
      cout << "LOGIN PAGE " << endl << endl;
      string email;
      cout << "Enter your email address: " << endl;
      cin >> email;
    

    // Log in as a user
    User* loggedInUser = login(email); //returns pointer to a user

  //if user does not yet exist, creates a new user and adds it to vector userVector
    if (loggedInUser == NULL) {
        cout << "\nUser not found, creating new account with email: " << email << endl;
        User newUser(email); // create a new User object
        userVector.push_back(newUser); // add the new user to the userVector
        loggedInUser = &userVector.back(); // set loggedInUser to point to the newly created user
        
    } else { //if user already exists, assign that as the address of the loggedInUser pointer
        cout << "SUCCESS! NOW LOGGED IN AS " << loggedInUser->getID() << endl;
        cout << "What would you like to do?" << endl<<endl;

      cout << "(1) SEARCH FLIGHTS" << endl;
      cout << "(2) PRINT ALL EXISTING TICKETS" << endl;
      cout << "(0) EXIT" << endl << endl;

      int num = (loggedInUser->getMyPassengers()).size(); //stores number of passengers in myPassengers 
      cin >> choiceMain;
      while(choiceMain == "2"){
          for (Passenger passenger : loggedInUser->getMyPassengers()) {
                            passenger.printPassengerDetails();
                            passenger.printTicket(num);
                        }
          cout << "What would you like to do?" << endl<<endl;
          cout << "(1) SEARCH FLIGHTS" << endl;
          cout << "(2) PRINT ALL EXISTING TICKETS" << endl;
          cout << "(0) EXIT" << endl << endl;
          cin >> choiceMain;
      }
      if(choiceMain=="0"){ //exits
        return 0;
      }

    }

    

    //system("clear");
      string from;
      string to;
      
      // displaying options for origin
        cout << "-------------------------------------------------------------------------" <<endl;

        cout << "\nWHERE ARE YOU TRAVELING FROM?" << endl << endl; // displaying options for origin

        cout << "\nType out your city of origin using ONLY LETTERS and SPACES.\n\nPress (0) to EXIT." << endl << endl;

        cout << "-------------------------------------------------------------------------" <<endl;

        getline(cin, from);
        getline(cin, from);
        
        if(exit=="0"){//option to exit
            return 0;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
        system("clear");

        // displaying options for destination
        cout << "\nWHERE ARE YOU TRAVELING TO?" << endl << endl; 

        cout << "\nType out your destination city using ONLY LETTERS and SPACES.\n\nPress (0) to EXIT." << endl << endl;
        cout << "-------------------------------------------------------------------------" <<endl;

      getline(cin, to);
        if(exit=="0"){ //option to exit
            return 0;
        }
        
        //checks that destination is not the same as origin
        while(from == to){
            cout << "\nYou are already there! Enter a valid destination." << endl<< endl;
            cin >> to;
            exit=stoi(to);
            if(exit=="0"){//option to exit
                return 0;
            }
        }

        //capitalises strings 'to' and 'from'
        for (int i=0; i<to.length(); i++){ 
            to[i] = toupper(to[i]);
        }
        for (int i=0; i<from.length(); i++){
            from[i] = toupper(from[i]);
        }
      
      system("clear");

      cout << "-------------------------------------------------------------------------" <<endl;

      cout << "\nYou want to travel from '" << from << "' to '" << to << "'."<< endl << endl;
      cout << "-------------------------------------------------------------------------" <<endl;

      //confirming choice of user
      cout << "Press (1) to confirm. Press (0) to exit." << endl<< endl;
        cin>>exit;
        if(exit=="0"){//option to exit
            return 0;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
     
     system("clear");

        //takes the date that the user wants to travel on

        cout << "\nEnter the DAY you would like to travel on in NUMERICAL value." << endl<< endl;
        int chosenDay;
        cin >> chosenDay;
        while(chosenDay>31){
          cout << "\nPlease enter a valid day." << endl<< endl;
          cin >> chosenDay;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
        
        system("clear");

        cout << "\nEnter the MONTH you would like to travel on in NUMERICAL value." << endl<< endl;
        int chosenMonth;
        cin >> chosenMonth;
        while(chosenMonth>12 || chosenMonth <=0){
          cout << "\nPlease enter a valid month." << endl<< endl;
          cin >> chosenMonth;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
      
        system("clear");

        cout << "\nEnter the YEAR you would like to travel on in NUMERICAL value." << endl<< endl;
        int chosenYear;
        cin >> chosenYear;
        while(chosenYear<2023){
          cout << "\nPlease enter a valid year." << endl<< endl;
          cin >> chosenYear;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
        
        system("clear");
      
        //creates vectors of flights by calling functions
        vector<Flight> flightsList = createFlights(chosenDay, chosenMonth, chosenYear, from, to);
        vector<BusinessClass> businessFlights = createBusinessFlights(chosenDay, chosenMonth, chosenYear, from, to);

        //prints flights based on user input
        displayFlights(flightsList, businessFlights, chosenDay, chosenMonth, chosenYear, from, to);
        cout << "-------------------------------------------------------------------------" <<endl;
        cout << "-------------------------------------------------------------------------" <<endl;

        //stores desired flight Number
        cout << "\n\nPlease enter the FLIGHT NUMBER of the flight you want to book." << endl<<endl;
        int FlightNumber1;
        cin >> FlightNumber1;
        cout << "-------------------------------------------------------------------------" <<endl;
        
        system("clear");

        cout << "\n\nPlease enter the NUMBER OF SEATS you would like to book for" << endl<<endl;
        int numSeats;
        cin >> numSeats;
        
        cout << "-------------------------------------------------------------------------" <<endl<<endl;

        //stores desired flight's index
        int flightIndex =0;
        Flight flight;

        //if flight Number is bigger than 1000000, its a business flight, look through business class flights to find flightIndex
        if(FlightNumber1>1000000){
          for (auto& flight : businessFlights) {
                  if(flight.getFlightNumber() == FlightNumber1){
                    break;
                  }
                  flightIndex++; 
              }
            flight = businessFlights.at(flightIndex); //assign the business class flight at this index to object flight
        }
        //else if flight Number is smaller than 1000000, its an economy flight, look through economy class flights to find flightIndex
        else if(FlightNumber1<=999999){
          for (auto& flight : flightsList) {
                  if(flight.getFlightNumber() == FlightNumber1){
                    break;
                  }
                  flightIndex++;
              }
              flight = flightsList.at(flightIndex);//assign the economy class flight at this index to object flight
        }
          
        //adds as many passengers as number of seats inputted by user
        for(int i = 0; i<numSeats; i++){
        flight.addPassengers(loggedInUser, flight);;
        }
        cout << "-------------------------------------------------------------------------" <<endl;
        
        system("clear");

                int choose;
                cout << "Would you like to add more seats? Press '1' for YES and '0' for NO" << endl << endl;
                cin >> choose;
                bool seatVerifier = true;

                //do while loop to expand vector as long as the use keeps adding passengers
                 while (choose != 0 && seatVerifier == true){
                      while (choose != 0 && choose != 1) {
                          cout << "Would you like to add more seats? Press '1' for YES and '0' for NO" << endl << endl;
                          cin >> choose;
                      }

                      int add;
                      
                      if (choose == 1) {
                            // cout << "\n How many seats would you like to ?" << endl << endl;
                            // cin >> add;

                            // while (add < 0) {
                            //     cout << "\n Please enter a positive integer." << endl << endl;
                            //     cin >> add;
                            // }
                        
                          for (int j = numSeats; j < numSeats+1; j++){
                              seatVerifier = flight.addPassengers(loggedInUser,flight);
                              if (seatVerifier == true) j = numSeats+1;
                          }
                          
                          system("clear");

                          cout << "\n Your current list of Passengers is:" << endl << endl;

                          for (Passenger passenger : flight.getPassengerList()) {
                            passenger.addFlightBooked(flight);
                            passenger.printPassengerDetails();

                              
                          }     
                          numSeats = numSeats+1;

                      }
                      
                      cout << "Would you like to add more seats? Press '1' for YES and '0' for NO" << endl << endl;
                      cin >> choose; 
                }
                cout << "-------------------------------------------------------------------------" <<endl;
                
                system("clear");

                //prints final list of passengers
                cout << "\nYour final list of Passengers is:" << endl << endl;

                    for (Passenger passenger : flight.getPassengerList()) {
                        passenger.printPassengerDetails();
                        // passenger.printTicket(num);
                    } 

                system("clear");
                int num = (loggedInUser->getMyPassengers()).size();

                  //allows the creation of a different random number every time the compiler runs
                  std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

                  // Create a uniform integer distribution between 100000 and 999999
                  std::uniform_int_distribution<int> otp(100000, 999999);
                  
                  //create new variables for card payment
                  string cardholder1;
                  string cardholder2;
                  int cardNumber;
                  int userOTP;
                  int ccv;
                  int check;

                  //Payment process
                  int singlePrice = flight.getTicketPrice();
                  int Totalprice = 0;
                  int ticket = 1;
                  cout << "PAYMENT DETAILS: " << endl << endl;
                  for (Passenger passenger : flight.getPassengerList()) { //gets total price by adding price of each passenger's ticket
                    Totalprice = Totalprice + flight.getTicketPrice();
                    } 
                   
                  cout << "-------------------------------------------------------------------------" <<endl <<endl;
                  cout << "$" << singlePrice << " x " << numSeats << " tickets = $" << Totalprice << endl<<endl;
                  cout << "-------------------------------------------------------------------------" <<endl <<endl;
                  cout << "Your total amount is: $" << Totalprice << endl << endl;
                  cout << "-------------------------------------------------------------------------" <<endl << endl;
                  
                  cout << "Enter cardholder FIRST name: " << endl;
                  cin >> cardholder1;
                  cout << "Enter cardholder SECOND name: " << endl;
                  cin >> cardholder2;
                  cout << "Enter card number: " << endl;
                  cin >> cardNumber;
                  cout << "Enter CCV on the back of the card: " << endl;
                  cin >> ccv;
                  cout<< "Waiting for OTP...";
                  cout.flush(); 
                  sleep(2); //creates a 2 second pause before printing the OTP message 
                  cout << "-------------------------------------------------------------------------" <<endl;
                  userOTP = otp(rng);
                  system("clear");
                  
                  cout<< "\n\nNew Message! Your OTP from AirLeens is: " << userOTP << endl;
                  cout << "-------------------------------------------------------------------------" <<endl;
    
                  cout << "Enter your OTP to confirm payment: " << endl;
                  cin >> check;
                  system("clear");
                  //if user inputs the correct OTP, 'print ticket' to create tsv file on sidebar
                  if(userOTP == check){
                    cout << "Payment Successful!" << endl;
                    cout << "Your ticket(s) are being printed..." << endl;
                     for (Passenger passenger : loggedInUser->getMyPassengers()) {
                        passenger.printPassengerDetails();
                        passenger.printTicket(num);
                    } 
                    cout << "-------------------------------------------------------------------------" <<endl;
                    cout << "Your ticket(s) have been saved to the files on the sidebar." << endl << endl;
                    cout << "Thank you for using AirLeens." << endl;
                    cout << "-------------------------------------------------------------------------" <<endl;

                    cout << "Press (1) to LOG OUT and go to MAIN PAGE, press (0) to EXIT PROGRAM." << endl;
                    cin >> mainmenu;
                  }

                  else{
                    cout << "Incorrect OTP! Sorry, you will have to restart!" << endl;
                    mainmenu =1;
                  }
                
                    

                
    }while(mainmenu == 1); //repeats entire loop while user selects (1) - MAIN MENU
    
    return 0;

  }

 