#include <string>
#include <vector>
#include "Passenger.h"
#include "Seat.h"

#ifndef FlightHeaderFile
#define FlightHeaderFile

class Flight
{
	private:
		std::string flightNumber;
		int numRows;
		int numSeats;
		char** seatMap;
		std::vector<Passenger> passengers;
		int sizeOfPassengerList;
		void destroy();
	public:
		Flight();
		Flight(int r, int s, std::string name);
		~Flight();
		Flight(const Flight& f);
		Flight& operator=(const Flight& f);
		
		
		std::string getFlightNumber()const;
		int getNumRows()const;
		int getNumSeats()const;
		int getSizeOfPassengerList()const;
		char** getSeatMap()const;
		std::vector<Passenger> getPassengerList()const;
		
		void setSizeOfPassengerList(int length);
		void setNumRows(int r);
		void setNumSeats(int s);
		void setFlightNumber(std::string flightNum);
		
		void addPassenger(Passenger p);
		int removePassenger(int id);
	
};

#endif