#include <string>
#include "Passenger.h"
#include "Seat.h"

Passenger::Passenger()
{
	id = 0;
}

Passenger::Passenger(std::string fName, std::string lName, std::string phoneNum, Seat s, int passengerId)
{
	firstName = fName;
	lastName = lName;
	phoneNumber = phoneNum;
	seat = s;
	id = passengerId;
}
		
std::string Passenger::getFirstName()const
{
	return firstName;
}

std::string Passenger::getLastName()const
{
	return lastName;
}

std::string Passenger::getPhoneNumber()const
{
	return phoneNumber;
}

Seat Passenger::getSeat()const
{
	return seat;
}

int Passenger::getId()const
{
	return id;
}
		
void Passenger::setFirstName(std::string& fName)
{
	firstName = fName;
}

void Passenger::setLastName(std::string& lName)
{
	lastName = lName;
}

void Passenger::setPhoneNumber(std::string& phoneNum)
{
	phoneNumber = phoneNum;
}

void Passenger::setSeat(Seat& s)
{
	seat = s;
}

void Passenger::setId(int passengerId)
{
	id = passengerId;
}
