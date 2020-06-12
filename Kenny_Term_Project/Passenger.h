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
		Passenger();
		Passenger(std::string fName, std::string lName, std::string phoneNum, Seat s, int passengerId);
		
		std::string getFirstName()const;
		std::string getLastName()const;
		std::string getPhoneNumber()const;
		Seat getSeat()const;
		int getId()const;
		
		void setFirstName(std::string fName);
		void setLastName(std::string lName);
		void setPhoneNumber(std::string phoneNum);
		void setSeat(Seat s);
		void setId(int passengerId);
};

#endif