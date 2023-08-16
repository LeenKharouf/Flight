# Report

## Introduction
The main objective of this project is to provide a user-friendly interface that allows customers to book flights for passengers and manage their bookings - a representation of a scaled-down version of a flight reservation system used by airline companies to manage their flight bookings. A system like this should be able to allow users to search for available flights, select their preferred travel dates and destinations, and book their tickets online. The importance of this in the real world is its ability to save time and effort for both the passenger and the airline staff. The program is designed to maintain a database of flights and their associated details, including flight numbers, departure and arrival times, and available seats. It also provides the capability to book seats and store passenger information for each flight.

The ability to store passenger information, such as name, contact details, and passport number can be used for ticket issuance, security checks, and boarding procedures. It would store flight schedules, seat availability, and fare information. This can help airline staff manage bookings, allocate seats, and set prices based on demand.

Generating electronic tickets or boarding passes for passengers is an important aspect of a flight reservation system - they can be printed or saved on passengers' mobile devices. This can streamline the check-in and boarding processes and reduce the need for paper tickets.

The user interface of the system is developed using C++ graphics libraries, providing a simple and intuitive interface that allows users to search for their flight and prints their tickets. It would allow the user to login and keep their information stored for the next time they come to book a flight.

After choosing the flight, the system will process payments for flight bookings through credit card payments. This can help airlines collect revenue more efficiently and securely.

The implementation of this project involves the use of several key object-oriented programming concepts, including inheritance and polymorphism. These principles enable the development of a scalable system that can be maintained and extended if necessary. This report details the design and implementation of the system, as well as its functionality and potential areas for improvement.


__________
__________

## Approach

**Defining requirements**: By identifying the requirements of the system, we can get to know the needs of an airline company and the customers' expectations for a flight booking system. This step will help to establish a clear scope of the project and define the functionalities that need to be implemented.

**Designing the system**: Creating a detailed design for the system will allow the system to be visualised. Defining the classes and objects that will be used in the system and specifying the interactions between the different components means that there would be a clear plan to follow. This could be a simple version of a pseudocode or a flowchart, or any representation of the system.

**Implement the system**: Once the design is complete, the system is implemented usse object-oriented programming principles to create classes and objects that represent the different components of the system. Ensure that the code is  scalable, making it easy to maintain and extend in the future.

**Develop the user interface**: After writing the main part of the code, the one that takes care of execution, it is important to ensure that there is a user-friendly interface that allows customers to easily book flights and choose their preferences, and provides real-time feedback to the user.

Testing & Refining the system: Test functions with different inputs from the user. This will let us know what restrictions to put on some variables and how to lay out the code to the user to ensure that the code doesn't break.

Here, we can also optimise the performance of the system by adding some of the code to make it optimal, e.g. inline functions, later mentioned in the report.

__________
__________

## Solution

To start off, a representation of how the code works is found in the flowchart below:
![Flowchart of system](images/flowchart2.png)

__________
__________
### Part 1
__________
__________
The first part of the code asks the user for their email, which can be referred to as the 'User ID'. 

```c++
User* login(string id) { // returns a pointer to the current user 
    for (int i = 0; i < userVector.size(); i++) {
        if (userVector[i].getID() == id) {
            return &userVector[i];
        }
    }
    return NULL; // User not found
}

```
The login() function takes an ID as an argument and searches through the userVector to find a User object with a matching ID. If a matching User object is found, a pointer to that object is returned. If no matching User object is found, a null pointer is returned to indicate that the user could not be found.
It to be stored in a vector of type User. It looks through the vector of existing Users and, if it cannot find it,  

```c++
if (loggedInUser == NULL) {
        cout << "\nUser not found, creating new account with email: " << email << endl;
        User newUser(email); // create a new User object
        userVector.push_back(newUser); // add the new user to the userVector
        loggedInUser = &userVector.back(); // set loggedInUser to point to the newly created user
        
    }
```
This code checks whether loggedInUser is a null pointer. If loggedInUser is null, it means that the user is not currently logged in. In this case, the code creates a new user account with the email address email and adds the new user to the userVector container using the push_back() function.

After adding the new user to userVector, the code sets loggedInUser to point to the newly created user by assigning it the address of the last element in userVector using the back() function.

Essentially, if the user is not logged in, this code creates a new user account and sets loggedInUser to point to that new account, so that the user can access their account and use the system. 

This feature also means that once a user has finished booking a flight, logged out, and logged back in, it would allow them to log back in again with the same username without having to create a new User as it has been saved due to the pointer.

^**OPTIMISATION CONCEPT 4** - The use of pointers - when a pointer to an object or data structure is passed, only the address of the original object or data structure is passed, which is typically much smaller than the entire object or data structure. This reduces the amount of memory required to pass the argument to a function and saves time.

__________
__________
### Part 2
__________
__________
The second part of the code takes in values from the user that are then used as parameters to create a vector of flights. Obviously, in reality, there would be a huge database of flights already created, and the flights would be managed by an admin account. For now, as this acts only as a simulation of a flight reservation system, it would create 13 flights that all match the user’s requirements in terms of origin, destination, and date. 

The function createFlights() would generate random numbers for the flight numbers and the prices within a given range. The snippet of the code shown below shows the section that does this:

```c++
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a uniform integer distribution between 250 and 350
    std::uniform_int_distribution<int> dist(250, 350);
    std::uniform_int_distribution<int> num(100000, 999999);

    int price = dist(rng); //assigns random number in the range of dist defined above
    int flightNumber = num(rng); //assigns random number in the range of num defined above
```


This code defines and initializes a random number generator using the **Mersenne Twister** algorithm, a high-quality pseudorandom number generator.

- ```c++std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());```
This initializes an instance of the std::mt19937 class with a seed based on the current time, using the std::chrono::system_clock and time_since_epoch() functions. This ensures that the seed value is different every time the program runs, which helps to generate different random sequences.

- ```c++ std::uniform_int_distribution<int> ```
This part creates two instances of the class, 'dist' and 'num'. The first distribution generates random integers between 250 and 350, for prices, while the second distribution generates random integers between 100000 and 999999, for flight numbers. 

- ```c++ int random_int = dist(rng);``` 
This is the way one would use the distributions with the random number generator rng to generate random integers within the specified ranges.


__________
__________
### Part 3
__________
__________
In order to print this list of flights, I made a for loop 
```c++
for (auto& flight : flightsList) {
            cout << "Flight number: " << flight.getFlightNumber() << " from: " << flight.getOrigin() << " to " << flight.getDestination() 
            << " on "<< flight.getDay() << "/" << flight.getMonth() << "/" << flight.getYear() <<  " at " << flight.getHour() << ":" << flight.getMin() << " | Price = $" << flight.getTicketPrice() << " | Class: " << flight.getStatus()<< endl<<endl;
        }
```
This code snippet is a loop that iterates through a list of flights (a vector of type Flight), and for each flight, it prints out various pieces of information about the flight, such as the flight number, origin, destination, date, time, ticket price, and status.

- ```c++ The for (auto& flight : flightsList)```   
This statement is a range-based for loop that iterates over each element of the flightsList vector, where flight is a reference to each Flight in flightsList.


^**OPTIMISATION CONCEPT 3** - This is an example of passing by reference, and is shown more clearly when passing the parameters into the function 'displayFlights()'. This is an example of optimisation because it allows the function to directly access the original vector without making a copy. This is more efficient because it avoids the overhead of making a copy and can be faster and use less memory.


The output of this code is shown below:
![img caption text](images/flightsList.png)


__________
__________
### Part 4
__________
__________
The next part of the code allows the user to pick the flight number of the flight they want. This flight is then assigned to a Flight object and is used, alongside Passenger class, to add and create vectors that store the user's passengers and their flights booked. 
```c++ 
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
```
- This function adds a new passenger to a flight and updates the user's passenger list if there is an available seat on the flight. It takes two arguments: a pointer to the loggedInUser who wants to book a seat on the flight, and the flight object that the user wants to book.

- If there are available seats on the flight, the function proceeds to create a new Passenger object using the createNewPassenger function, passing in the numSeats and flight objects. The numSeats variable is then incremented to indicate that a new passenger has been added to the flight.

- The addFlightBooked function is then called on the new Passenger object to add the flight to the vector of flightsBooked for the passenger. The new Passenger object is then added to the flightPassengers vector, which keeps track of all passengers on the flight.

- Finally, the new Passenger object is also added to the user's myPassengerList vector by calling the addPassenger function on the loggedInUser object. The function returns true to indicate that the passenger was successfully added to the flight.

^**OPTIMISATION CONCEPT 1** - Vectors provide a dynamic array implementation that allows efficient and flexible storage of elements in contiguous memory, providing constant-time access to elements and reduces constant-time complexity for appending elements.

They have built-in support for a wide range of operations, such as resizing, sorting, searching, and inserting, making them a convenient and efficient container for managing large datasets. Additionally, vectors provide automatic memory management, eliminating the need for manual memory allocation and deallocation, which can be error-prone and time-consuming.

Overall, using vectors can help optimize memory usage and improve the performance of code that involves managing and processing large amounts of data, especially when the size of the data is initially unknown, like the number of Passengers.
__________
__________
### Part 4
__________
__________
In order to add to or iterate through the vector of passengers on the flight, we need getter functions.
BusinessClass is a subclass of the Flight class, which means it has been derived from it and contains the same members & functions as Flight, but it could have differnet versions of these functions.

The example below shows 


The code below shoes the way BusinessClass is created
```c++ 
class BusinessClass : public Flight
```
Here, we can see the function in the Flight class. It returns the vector specific to the objects of class Flight.
```c++ 
virtual vector<Passenger> getPassengerList(){
        return flightPassengers;
    }
```
In order to get the Business flight passengers' list, we would create the same function but return a differnet vector
```c++ 
vector<Passenger> getPassengerList(){
     return businessPassengers;
    }
```
^**OOP CONCEPT 2, 3, 4** - The use of virtual functions allow the derived class to override the function of the parent class, which is a feature of the use of inheritance.


__________
__________
### Part 5
__________
__________

**OPTIMISATION CONCEPT 2** - The last optimisation concept is shown below. This function is called a lot in the main(), and declaring it as an 'inline' function can make the program faster because it eliminates the overhead associated with function calls every time.

```c++ 
 inline Passenger createNewPassenger(int seat, Flight flight) {
            Passenger passenger;
            passenger.setPassengerDetails(seat, flight);
            passenger.printPassengerDetails();
   return passenger;
}
```

__________
__________
### Part 6
__________
__________
At the end of the program, the function printTickets() creates an ofstream object called outfile to write to the file.

The code then enters a loop which iterates over all flights that the passenger has booked. For each flight, the code opens the file named document using the open() function of the ofstream object. The code then writes some details about the passenger's flight into the file.

```c++ 
string document = getLastName() + "_" + getFirstName() + "_Ticket" + to_string(num) + ".txt";            
            ofstream outfile;

            for (int i = 0; i < flightsBooked.size(); i++) {
                // open file for writing
                outfile.open(document);
```

The variable 'num' represents the number of passengers that have been created by the current User. This is so that files dont end up having the same name if it is a repeated passenger.

__________
## References
__________
__________

https://www.positioniseverything.net/invalid-use-of-incomplete-type/

https://stackoverflow.com/questions/73505700/clang-error-no-such-file-or-directory-2-clang-error-no-input-files-erro

https://stackoverflow.com/questions/56177988/invalid-operands-to-binary-expression-string-to-string-aka-basic-string

https://www.geeksforgeeks.org/toupper-function-in-c/

https://www.geeksforgeeks.org/toupper-function-in-c/

https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus

https://www.emirates.com/english/

https://www.reddit.com/r/learnprogramming/comments/wzozto/this_error_is_showing_terminate_called_after/

https://www.geeksforgeeks.org/map-insert-in-c-stl/

https://github.com/x-labs-xyz/public--OOP-Spring23

https://www.techiedelight.com/check-given-key-exists-map-cpp/