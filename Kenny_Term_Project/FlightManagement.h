#include <string>
#include <vector>
#include "Passenger.h"
#include "Seat.h"

#ifndef FlightManagementHeaderFile
#define FlightManagementHeaderFile

#define TEXTFILENAME "flight_info.txt"

//PROMISES: Displays the initial message at the beginning of the program to the screen
void displayInitialMessage();

//PROMISES: Displays the 6 menu options to the screen
void displayOptions();

//PROMISES: Asks for user input to choose a menu options
//          Repetitively asks until the input is one char from '1' to '6' inclusive then returns it
char selectOption();

//REQUIRES: currentRow must be a valid row on the airplane
//PROMISES: This function will print the row of the airplane for the seat map showing which seats are taken
//          as well as a line to divide the row from the next
void printRows(const Flight& f, int currentRow);

//PROMISES: This function reads the text file defined above
//          If the file is of the proper form then it creates a Flight object with the data and returns it
//          Otherwise, this function displays a message and exits the program
Flight readTextFile();

//PROMISES: This function asks the user if they want to write into the text file
//          It continues to ask until the user inputs either 'Y' or 'N'
//          If 'Y' it writes the data of f into the text file defined above. Otherwise it does nothing
void writeTextFile(const Flight& f);

//REQUIRES: flight be a valid Flight object with non zero numRows and numSeats
//PROMISES: displays the aircraft seat map showing which seats are occupied
void displayAircraftSeatMap(const Flight& flight);

//REQUIRES: the totalTextLength must be greater or equal to the legth of the string text
//PROMISES: This function prints the string text centered in the field of size totalTextLength
void printCenteredText(int totalTextLength, const std::string& text);

//PROMISES: prints a table showing the list of passengers (if any)
void showPassengerInformation(const Flight& f);

//PROMISES: displays a request for the user to press enter and stalls until the user does so
void pressReturn();

//PROMISES: Prompts the user for values for some member variables of a passenger and continues prompting until input is valid,
//          then creates the Passenger and adds it to the flight
void addPassenger(Flight& flight);

//REQUIRES: flight must have at least one passenger
//PROMISES: Prompts the user for a valid id then removes it from the flight list
void removePassenger(Flight& flight);

//REQUIRES: excess white space must be removed before calling this function
//PROMISES: returns 1 if the name is between 0 and 19 characters inclusive, 0 otherwise
int checkIfNameIsValid(const std::string& name);

//PROMISES: removes leading and trailing white space from the string
void removeExcessSpaces(std::string& str);

//REQUIRES: the phone number must be 10 numbers
//PROMISES: puts the phone number in the form XXX-XXX-XXXX where X is an integer number from '0' to '9' inclusive
void formatPhoneNumber(std::string& phoneNum);

//PROMISES: returns 1 if the phone number is 10 integer numbers (may have white space or dashes in between). Otherwise returns 0
int checkIfPhoneNumberIsValid(const std::string& phoneNum);

//REQUIRED: flight's numRows and numSeats should not be zero
//PROMISES: returns the char that is stored in strSeat. If it is empty, holds more than one char, or the char does not match
//          the number of seats in flight, returns 0
char returnValidSeat(const Flight& flight, const std::string& strSeat);

//REQUIRED: flight's numRows and numSeats may not be zero
//PROMISES: returns the row number in strRow as an integer if it is valid, otherwise it returns 0
int returnValidRow(const Flight& flight, const std::string& strRow);

//REQUIRES: row and seat must possible in flight (flight must have that row and that seat)
//PROMISES: returns 1 if that seat is occupied by a passenger, 0 if it is empty
int isSeatTaken(const Flight& flight, int row, char seat);

//PROMISES: if the id already belongs to a passenger, returns 1. 0 otherwise
int isIdTaken(const Flight& flight, int id);

//PROMISES: returns 1 if s can be converted into a valid int. Returns 0 if it cannot
int validInt(const std::string& s);

//PROMISES: returns the int stored in s as an int. returns 0 if it cannot be converted to an int
int convertStrtoInt(const std::string& s);

#endif