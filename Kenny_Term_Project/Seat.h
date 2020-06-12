#ifndef SeatHeaderFile
#define SeatHeaderFile

class Seat
{
	private:
		int row;
		char seat;
	public:
		Seat();
		Seat(int row, char seat);
		int getRow()const;
		char getSeat()const;
		void setRow(int r);
		void setSeat(char c);
};

#endif