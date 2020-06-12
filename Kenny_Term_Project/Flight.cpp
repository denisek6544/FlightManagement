#include <string>
#include <iostream>
#include <iomanip>
#include "Flight.h"
#include <vector>

Flight::Flight()
{
	flightNumber = "";
	numRows = 0;
	numSeats = 0;
	sizeOfPassengerList = 0;
	seatMap = nullptr;
}

Flight::Flight(int r, int s, std::string name)
{
	flightNumber = name;
	numRows = r;
	numSeats = s;
	sizeOfPassengerList = 0;
	seatMap = new char*[r];
	if(seatMap == nullptr)
	{
		std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
		exit(1);
	}
	for(int i = 0; i < r; i++)
	{
		*(seatMap + i) = new char[numSeats];
		if(*(seatMap + i) == nullptr)
		{
			std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
			exit(1);
		}	
		for(int j = 0; j < s; j++)
		{
			seatMap[i][j] = ' ';
		}
	}
}

void Flight::destroy()
{
	for(int i = 0; i < numRows; i++)
	{
		delete[] seatMap[i];
	}
	delete seatMap;
}

Flight::~Flight()
{
	destroy();
}

Flight::Flight(const Flight& f)
{
	flightNumber = f.flightNumber;
	numRows = f.numRows;
	numSeats = f.numSeats;
	passengers = f.passengers;
	sizeOfPassengerList = f.sizeOfPassengerList;
	seatMap = new char*[numRows];
	if(seatMap == nullptr)
	{
		std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
		exit(1);
	}
	for(int i = 0; i < numRows; i++)
	{
		*(seatMap + i) = new char[numSeats];
		if(*(seatMap + i) == nullptr)
		{
			std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
			exit(1);
		}	
		for(int j = 0; j < numSeats; j++)
		{
			seatMap[i][j] = ' ';
		}
	}

}

Flight& Flight::operator=(const Flight& f)
{
	if(this != &f)
	{
		destroy();
		
		flightNumber = f.flightNumber;
		numRows = f.numRows;
		numSeats = f.numSeats;
		passengers = f.passengers;
		sizeOfPassengerList = f.sizeOfPassengerList;
		seatMap = new char*[numRows];
		if(seatMap == nullptr)
		{
			std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
			exit(1);
		}
		for(int i = 0; i < numRows; i++)
		{
			*(seatMap + i) = new char[numSeats];
			if(*(seatMap + i) == nullptr)
			{
				std::cout<<"The allocation of memory failed. This program will now end"<<std::endl;
				exit(1);
			}	
			for(int j = 0; j < numSeats; j++)
			{
				seatMap[i][j] = ' ';
			}
		}
	}
	return *this;
}



void Flight::setFlightNumber(std::string flightNum)
{
	flightNumber.clear();
	flightNumber = flightNum;
}

std::string Flight::getFlightNumber()const
{
	return flightNumber;
}

void Flight::setNumSeats(int s)
{
	numSeats = s;
}

int Flight::getNumSeats()const
{
	return numSeats;
}

int Flight::getNumRows()const
{
	return numRows;
}

void Flight::setNumRows(int r)
{
	numRows = r;
}

int Flight::getSizeOfPassengerList()const
{
	return sizeOfPassengerList;
}

void Flight::setSizeOfPassengerList(int length)
{
	sizeOfPassengerList = length;
}

char** Flight::getSeatMap()const
{
	return seatMap;
}

std::vector<Passenger> Flight::getPassengerList()const
{
	return passengers;
}

void Flight::addPassenger(Passenger p)
{
	sizeOfPassengerList++;
	passengers.push_back(p);
	seatMap[p.getSeat().getRow() - 1][(int)(p.getSeat().getSeat()) - 65] = 'X';
}

int Flight::removePassenger(int id)
{
	int index;
	for(index = 0; index < sizeOfPassengerList; index++)
	{
		if(id == passengers.at(index).getId())
		{
			seatMap[passengers.at(index).getSeat().getRow() - 1][(int)(passengers.at(index).getSeat().getSeat()) - 65] = ' ';
			passengers.erase(passengers.begin() + index);
			sizeOfPassengerList--;
			return 1;
		}
	}
	return 0;
}
