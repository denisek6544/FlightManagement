#ifndef SeatHeaderFile
#define SeatHeaderFile

class Seat
{
	private:
		int row;
		char seat;
	public:
		//PROMISES: This default constructor sets the values of row and seat to zero
		Seat();
		
		//REQUIRES: r must be a positive integer not equal to zero
		//REQUIRES: c must be a char from 'A' to 'Z' inclusive
		//PROMISES: sets the value of the Seat's row to r and the Seat's seat to c
		Seat(int row, char seat);
		
		//PROMISES: Returns the value of the integer member variable row of the Seat object
		int getRow()const;
		
		//PROMISES: Returns the value of the char member variable seat of the Seat object
		char getSeat()const;
		
		//REQUIRES: r must be a positive integer not equal to zero
		//PROMISES: sets the value of the Seat's row to r
		void setRow(int r);
		
		//REQUIRES: c must be a char from 'A' to 'Z' inclusive
		//PROMISES: sets the value of the Seat's seat to c
		void setSeat(char c);
};

#endif