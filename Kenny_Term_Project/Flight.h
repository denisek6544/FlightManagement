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
		
		//PROMISES: deallocates the memory of seatMap
		void destroy();
		
		//PROMISES: *allocates memory for seatMap and makes seatMap a copy of the seatMap of flight
		//          *if flight is a null pointer then it creates a blank seatMap (every element is ' ')
		void createSeatMap(const Flight* flight);
		
	public:
		//PROMISES: initializes numRows and numSeats to 0 and initializes seatMap to nullptr
		Flight();
		
		//REQUIRES: *r and s must be > 0
		//          *name must not be an empty string
		//PROMISES: *initializes numRows to r, numSeats to s, and flightNumber to name
		//          *initializes seatMap to be an empty map (all elements ' ')
		Flight(int r, int s, const std::string& name);
		
		//PROMISES: deallocates the memory of seatMap
		~Flight();
		
		//REQUIRES: f must be a valid Flight object
		//PROMISES: Initializes the Flight object to be the same as f but with independent dynamically allocated memory for seatMap
		Flight(const Flight& f);
		
		//REQUIRES: f must be a valid Flight object
		//PROMISES: assigns the Flight object to the value of f but with independent dynamically allocated memory for seatMap
		Flight& operator=(const Flight& f);
		
		//PROMISES: returns the value of flightNumber
		std::string getFlightNumber()const;
		
		//PROMISES: returns the value of numRows
		int getNumRows()const;
		
		//PROMISES: returns the value of numSeats
		int getNumSeats()const;
		
		//PROMISES: returns a copy of seatMap
		char** getSeatMap()const;
		
		//PROMISES: returns a copy of passengers
		std::vector<Passenger> getPassengerList()const;
		
		//REQUIRES: r > 0
		//PROMISES: sets the value of numRows to r
		void setNumRows(int r);
		
		//REQUIRES: s > 0
		//PROMISES: sets the value of numSeats to s
		void setNumSeats(int s);
		
		//REQUIRES: flihtNum must be a reference to a not empty string
		//PROMISES: sets the value of flightNumber to flightNum
		void setFlightNumber(const std::string& flightNum);
		
		//REQUIRES: Passenger p is a reference to a valid Passenger
		//PROMISES: Adds the Passenger to the vector and updates the seatMap
		void addPassenger(const Passenger& p);
		
		//PROMISES: *Removes the passenger with the passengerId that matches id, updates the seatMap, and returns 1
		//          *If the id does not match that of any current passenger it returns 0 and nothing happens
		int removePassenger(int id);
};

#endif