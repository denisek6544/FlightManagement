
#include "Seat.h"

Seat::Seat()
{
	row = 0;
	seat = 0;
}

Seat::Seat(int r, char s)
{
	row = r;
	seat = s;
}

int Seat::getRow()const
{
	return row;
}

char Seat::getSeat()const
{
	return seat;
}

void Seat::setRow(int r)
{
	row = r;
}

void Seat::setSeat(char c)
{
	seat = c;
}
