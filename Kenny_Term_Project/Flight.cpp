#include <string>
#include <iostream>
#include <iomanip>
#include "Flight.h"
#include <vector>

Flight::Flight()
{
	numRows = 0;
	numSeats = 0;
	seatMap = nullptr;
}

Flight::Flight(int r, int s, const std::string& name)
{
	flightNumber = name;
	numRows = r;
	numSeats = s;
	
	createSeatMap(nullptr);
}

void Flight::destroy()
{
	for(int i = 0; i < numRows; i++)
	{
		delete[] seatMap[i];
	}
	delete seatMap;
}

void Flight::createSeatMap(const Flight* flight)
{
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
			if(flight == nullptr)
				seatMap[i][j] = ' ';
			else
				seatMap[i][j] = (*flight).seatMap[i][j];
		}
	}
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
	
	createSeatMap(&f);
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
		
		createSeatMap(&f);
	}
	return *this;
}


void Flight::setFlightNumber(const std::string& flightNum)
{
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

char** Flight::getSeatMap()const
{
	return seatMap;
}

std::vector<Passenger> Flight::getPassengerList()const
{
	return passengers;
}

void Flight::addPassenger(const Passenger& p)
{
	passengers.push_back(p);
	seatMap[p.getSeat().getRow() - 1][(int)(p.getSeat().getSeat()) - 65] = 'X';
}

int Flight::removePassenger(int id)
{
	int index;
	for(index = 0; index < int(passengers.size()); index++)
	{
		if(id == passengers.at(index).getId())
		{
			seatMap[passengers.at(index).getSeat().getRow() - 1][(int)(passengers.at(index).getSeat().getSeat()) - 65] = ' ';
			passengers.erase(passengers.begin() + index);
			return 1;
		}
	}
	return 0;
}
