#include <string>
#include "Seat.h"

#ifndef PassengerHeaderFile
#define PassengerHeaderFile

class Passenger
{
	private:
		std::string firstName;
		std::string lastName;
		std::string phoneNumber;
		Seat seat;
		int id;
		
	public:
		//PROMISES: This default constructor initializes the value of id to zero
		Passenger();
		
		//REQUIRES: *fName and lName must not be empty strings
		//          *phoneNum must not be an empty string. The string must be made up of chars from '0' to '9' inclusive, '-', and ' ' only
		//          *passengerId must be a positive integer not equal to zero
		//PROMISES: *The value of firstName will be set to fName, lastName will be set to lName,
		//          phoneNumber will be set to phoneNum, seat will be set to s, and id will be set to passengerId
		Passenger(std::string fName, std::string lName, std::string phoneNum, Seat s, int passengerId);
		
		std::string getFirstName()const;
		std::string getLastName()const;
		std::string getPhoneNumber()const;
		Seat getSeat()const;
		int getId()const;
		
		//REQUIRES: fName must not be an empty string
		//PROMISES: this function sets the value of the member variable firstName to fName
		void setFirstName(std::string& fName);
		
		//REQUIRES: lName must not be an empty string
		//PROMISES: this function sets the value of the member variable lastName to lName
		void setLastName(std::string& lName);
		
		//REQUIRES: phoneNum must not be an empty string. The string must be made up of chars from '0' to '9' inclusive, '-', and ' ' only
		//PROMISES: sets the value of phoneNumber to that of phoneNum
		void setPhoneNumber(std::string& phoneNum);
		
		//PROMISES: sets the value of seat to s
		void setSeat(Seat& s);
		
		//REQUIRES: passengerId must be a positive integer not equal to zero
		//PROMISES: sets the value of id to passengerId
		void setId(int passengerId);
};

#endif