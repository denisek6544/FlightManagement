#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Flight.h"
#include <vector>
#include "Seat.h"
#include "FlightManagement.h"

int main(void)
{
	Flight flight =  readTextFile();
	displayInitialMessage();
	char ch = 0;
	int charToNum;
	do
	{
		ch = selectOption();
		charToNum = ch - '0';
		
		switch(charToNum)
		{
			case 1:
				displayAircraftSeatMap(flight);
				break;
			case 2:
				showPassengerInformation(flight);
				break;
			case 3:
				addPassenger(flight);
				break;
			case 4:
				removePassenger(flight);
				break;
			case 5:
				writeTextFile(flight);
				break;
			case 6:
				std::cout<<"Program Terminated."<<std::endl;
				exit(1);
				break;
		}
	}while(ch != '6');
	return 0;
}

void addPassenger(Flight& flight)
{
	std::string strId;
	int id;
	
	while(1)
	{
		std::cout<<"Please enter the passenger id: ";
		getline(std::cin, strId, '\n');
		removeExcessSpaces(strId);
		id = convertStrtoInt(strId);
		if(id == 0)
		{
			std::cout<<"That is not a valid id. Please try again"<<std::endl;
		}
		else if(isIdTaken(flight, id))
			std::cout<<"That id is taken. Please choose another id"<<std::endl;
			
		else
			break;
	}
	
	std::string firstName;
	while(1)
	{
		std::cout<<"Please enter the passenger's first name: ";
		getline(std::cin, firstName, '\n');
		removeExcessSpaces(firstName);
		if(!checkIfNameIsValid(firstName))
			std::cout<<"That is not a valid first name. Please try again"<<std::endl;
		else
			break;
	}
	
	std::string lastName;
	while(1)
	{
		std::cout<<"Please enter the passenger's last name: ";
		getline(std::cin, lastName, '\n');
		removeExcessSpaces(lastName);
		if(!checkIfNameIsValid(lastName))
			std::cout<<"That is not a valid last name. Please try again"<<std::endl;
		else
			break;
	}
	
	std::string phoneNumber;
	while(1)
	{
		std::cout<<"Please enter the passenger's phone number: ";
		getline(std::cin, phoneNumber, '\n');
		removeExcessSpaces(phoneNumber);
		if(!checkIfPhoneNumberIsValid(phoneNumber))
			std::cout<<"That is not a valid phone number. Please try again"<<std::endl;
		else
			break;
	}
	formatPhoneNumber(phoneNumber);
	
	std::string strRow;
	int row;
	std::string strSeat;
	char seat;
	while(1)
	{
		std::cout<<std::endl;
		std::cout<<"Please enter the passenger's desired row: ";
		getline(std::cin, strRow, '\n');
		std::cout<<"Please enter the passenger's desired seat: ";
		getline(std::cin, strSeat, '\n');
		removeExcessSpaces(strRow);
		removeExcessSpaces(strSeat);
		row = returnValidRow(flight, strRow);
		seat = returnValidSeat(flight, strSeat);
		if(row == 0)
			std::cout<<"That row is not valid. Please try again."<<std::endl;
		else if(seat == 0)
			std::cout<<"That seat is not valid. Please try again."<<std::endl;
		else if(isSeatTaken(flight, row, seat))
			std::cout<<"That seat is taken. Please try again."<<std::endl;
		else
			break;
	}
	
	flight.addPassenger(Passenger(firstName, lastName, phoneNumber, Seat(row, seat), id));
	
	pressReturn();
}

char returnValidSeat(const Flight& flight, const std::string& strSeat)
{
	if(strSeat.size() != 1)
		return 0;

	if((strSeat.at(0) > (flight.getNumSeats() + 'A' - 1)) || (strSeat.at(0) < 'A'))
		return 0;
	
	return strSeat.at(0);
}

int returnValidRow(const Flight& flight, const std::string& strRow)
{
	int row = convertStrtoInt(strRow);
	if((row > flight.getNumRows()) || (row <= 0))
		return 0;
	return row;
}

int isSeatTaken(const Flight& flight, int row, char seat)
{
	if(flight.getSeatMap()[row - 1][seat - 'A'] == 'X')
		return 1;
	return 0;
}

int isIdTaken(const Flight& flight, int id)
{
	for(int i = 0; i < int(flight.getPassengerList().size()); i++)
	{
		if(id == flight.getPassengerList().at(i).getId())
		{
			return 1;
		}
	}
	return 0;
}

void removeExcessSpaces(std::string& str)
{
	while((str.size() != 0) && ((str.at(0) == ' ') || (str.at(0) == '\n') || (str.at(0) == '	')))
	{
		str.erase(0, 1);
	}
	
	while((str.size() != 0) && ((str.at(str.size() - 1) == ' ') || (str.at(str.size() - 1) == '\n') || (str.at(str.size() - 1) == '	')))
	{
		str.erase(str.size() - 1, 1);
	}
}
void formatPhoneNumber(std::string& phoneNum)
{
	int length = phoneNum.size();
	for(int i = 0; i < length; i++)
	{
		if((phoneNum.at(i) == ' ') || (phoneNum.at(i) == '-'))
		{
			phoneNum.erase(i, 1);
			length--;
			i--;
		}
	}
	phoneNum.insert(3, "-");
	phoneNum.insert(7, "-");
}

int checkIfPhoneNumberIsValid(const std::string& phoneNum)
{
	int length = phoneNum.size();
	for(int i = 0; i < int(phoneNum.size()); i++)
	{
		if((phoneNum.at(i) == ' ') || (phoneNum.at(i) == '-'))
		{
			length--;
		}
		else if((phoneNum.at(i) < '0') || (phoneNum.at(i) > '9'))
		{
			return 0;
		}
	}
	if(length != 10)
		return 0;
	return 1;
}

int checkIfNameIsValid(const std::string& name)
{
	if((name.size() > 19) || (name.size() == 0))
		return 0;
	return 1;
}

void removePassenger(Flight& flight)
{
	std::string strId;
	
	while(1)
	{
		std::cout<<"Please enter the id of the passenger that needs to be removed: ";
		getline(std::cin, strId, '\n');
		removeExcessSpaces(strId);
		int id = convertStrtoInt(strId);
		
		if(id == 0)
		{
			std::cout<<"That is not a valid id. Please try again"<<std::endl;
		}
		else if(!flight.removePassenger(id))
			std::cout<<"A passenger with that id does not exist. Please try again"<<std::endl;
		else
			break;
	}
	pressReturn();
}

int validInt(const std::string& s)
{
	int valid = 1;
	int i;

	if (int(s.size()) == 0)
		valid = 0;
	else if((int(s.size()) == 1) && ((s.at(0) == ' ') || (s.at(0) == '\n') || (s.at(0) == '	')))
		valid = 0;
	else
	{
		for(i = 0; i < int(s.size()); i++)
		{
			if(s.at(i) < '0' ||  s.at(i) > '9')
			{
				valid = 0;
				break;
			}
		}
	}
  
	return valid;
}

int convertStrtoInt(const std::string& s)
{
	int sum = 0;
	if(validInt(s))
	{
		int i;
		for(i = 0; i < int(s.size()); i++)
		{
			sum = 10 * sum + (s.at(i) - '0');
		}
	}
	else
		return 0;

	return sum;
}

void pressReturn()
{
	std::cout<<std::endl<<"<<<Press Return to Continue>>>";
	char c;
	do
	{
		c = getchar();
	}while (c != '\n');
	std::cout<<std::endl;
}

char selectOption()
{
	std::string input;
	displayOptions();
	while(1)
	{
		std::cout<<"Enter your choice: (1, 2, 3, 4, 5, or 6) ";
		getline(std::cin, input, '\n');
		removeExcessSpaces(input);
		if((input.size() != 1) || ((input.at(0) < '1') || (input.at(0) > '6')))
			std::cout<<"That is not an option. Please try again"<<std::endl;
		else
			break;
	}
	std::cout<<std::endl;
	return input.at(0);
}

void displayInitialMessage()
{
	std::cout<<"Version 1.0"<<std::endl;
	std::cout<<"Term Project - Flight Management Program in C++"<<std::endl;
	std::cout<<"Produced by: Denise Kenny"<<std::endl;
	pressReturn();
}

void displayOptions()
{
	std::cout<<"Please select one of the following options: "<<std::endl;
	std::cout<<"1. Display Flight Seat Map"<<std::endl;
	std::cout<<"2. Display Passengers Information"<<std::endl;
	std::cout<<"3. Add a New Passenger"<<std::endl;
	std::cout<<"4. Remove an Existing Passenger"<<std::endl;
	std::cout<<"5. Save data"<<std::endl;
	std::cout<<"6. Quit"<<std::endl;
	std::cout<<std::endl;
}

Flight readTextFile()
{
	std::ifstream inputStream(TEXTFILENAME);
	if(inputStream.fail())
	{
		std::cout<<"Opening the flight information text file failed. This program will now terminate";
		exit(1);
	}
	
	std::string currentLine;
	getline(inputStream, currentLine, '\n');
	removeExcessSpaces(currentLine);
	if(currentLine.size() == 0)
	{
		std::cout<<"This file is not valid. This program will now terminate";
		exit(1);
	}
	
	int newWord = 1;
	int secondStr = 0;
	int thirdStr = 0;
	
	for(int i = 0; i < int(currentLine.size()); i++)
	{
		if((currentLine.at(i) == ' ') || (currentLine.at(i) == '	'))
		{
			newWord = 1;
		}
		else if(newWord)
		{
			newWord = 0;
			if(secondStr == 0)
				secondStr = i;
			else if(thirdStr == 0)
				thirdStr = i;
			else
			{
				std::cout<<"This file is not valid. The program will terminate now"<<std::endl;
				exit(1);
			}
		}
	}
	
	if(secondStr == 0 || thirdStr == 0)
	{
		std::cout<<"This file is not valid. The program will terminate now"<<std::endl;
		exit(1);
	}
				
	std::string flightNum = currentLine.substr(0, secondStr);
	std::string numRowsStr = currentLine.substr(secondStr, thirdStr - secondStr);
	std::string numSeatsStr = currentLine.substr(thirdStr, 1);
	removeExcessSpaces(flightNum);
	removeExcessSpaces(numRowsStr);
	removeExcessSpaces(numSeatsStr);
	int numRows = convertStrtoInt(numRowsStr);
	int numSeats = convertStrtoInt(numSeatsStr);
	
	Flight flight(numRows, numSeats, flightNum);

	while(!inputStream.eof())
	{
		getline(inputStream, currentLine, '\n');
		if(currentLine.size() == 0)
			break;
		removeExcessSpaces(currentLine);
		std::string firstName = currentLine.substr(0, 20);
		removeExcessSpaces(firstName);
		std::string lastName = currentLine.substr(20, 20);
		removeExcessSpaces(lastName);
		std::string phoneNumber = currentLine.substr(40, 20);
		removeExcessSpaces(phoneNumber);
		std::string fullSeat = currentLine.substr(60, 4);
		removeExcessSpaces(fullSeat);
		std::string idStr = currentLine.substr(64, currentLine.size() - 64);
		removeExcessSpaces(idStr);
		
		std::string rowStr;
		char seat;
		for(int i = 0; i < int(fullSeat.size()); i++)
		{
			if(fullSeat.at(i) >= '0' && fullSeat.at(i) <= '9')
				rowStr.append(1, fullSeat.at(i));
			else if(fullSeat.at(i) >= 'A' && fullSeat.at(i) <= 'Z')
			{
				seat = fullSeat.at(i);
			}
		}
		
		removeExcessSpaces(rowStr);
		removeExcessSpaces(idStr);
		
		int row = convertStrtoInt(rowStr);
		int id = convertStrtoInt(idStr);

		Seat flightSeat(row, seat);
		flight.addPassenger(Passenger(firstName, lastName, phoneNumber, flightSeat, id));
	}
	inputStream.close();
	return flight;
}

void writeTextFile(const Flight& f)
{
	std::string input;
	do
	{
		std::cout<<"Do you want to save the data in "<<TEXTFILENAME<<"?"<<std::endl;
		std::cout<<"Please answer <Y or N>: ";
		getline(std::cin, input, '\n');
		removeExcessSpaces(input);
		if(input.size() == 1)
		{
			if(input.at(0) == 'Y')
				break;
			else if(input.at(0) == 'N')
			{
				pressReturn();
				return;
			}
		}
		std::cout<<"That input is not valid. Please try again"<<std::endl;
	}while(1);
	
	std::ofstream outputStream(TEXTFILENAME);
	if(outputStream.fail())
	{
		std::cout<<"Opening the flight information text file failed. This program will now terminate";
		exit(1);
	}
	outputStream<<std::left<<std::setw(9)<<f.getFlightNumber();
	outputStream<<std::setw(6)<<f.getNumRows();
	outputStream<<std::setw(1)<<f.getNumSeats()<<std::endl;
	for(int i = 0; i < int(f.getPassengerList().size()); i++)
	{
		outputStream<<std::setw(20)<<f.getPassengerList().at(i).getFirstName();
		outputStream<<std::setw(20)<<f.getPassengerList().at(i).getLastName();
		outputStream<<std::setw(20)<<f.getPassengerList().at(i).getPhoneNumber();
		outputStream<<std::setw(1)<<f.getPassengerList().at(i).getSeat().getRow();
		int field;
		if(f.getPassengerList().at(i).getSeat().getRow() < 10)
			field = 3;
		else
			field = 2;
		outputStream<<std::setw(field)<<f.getPassengerList().at(i).getSeat().getSeat()<<" ";
		outputStream<<std::setw(1)<<f.getPassengerList().at(i).getId();
		if(i != int(f.getPassengerList().size()) -1)
			outputStream<<std::endl;
	}
	outputStream.close();
	
	std::cout<<std::endl;
	std::cout<<"All the data in the passenger list was saved into "<<TEXTFILENAME<<std::endl;
	pressReturn();
}

void displayAircraftSeatMap(const Flight& flight)
{	
	std::string title("Aircraft Seat Map");
	printCenteredText((flight.getNumSeats() * 4) + 4, title);
	
	std::cout<<"     ";
	for(int i = 65; i < (65+flight.getNumSeats()); i++)
	{
		std::cout<<(char)i<<"   ";
	}
	std::cout<<std::endl;
	
	std::cout<<"   +";
	for(int i = 0; i < flight.getNumSeats(); i++)
	{
		std::cout<<"---+";
	}
	std::cout<<std::endl;
	
	for(int i = 0; i < flight.getNumRows(); i++)
	{
		printRows(flight, i);
	}
	pressReturn();
}

void printRows(const Flight& flight, int currentRow)
{
	std::cout << std::left;
	std::cout<< std::setw(3) << currentRow + 1 << "|";
	for(int i = 0; i < flight.getNumSeats(); i++)
	{
		std::cout<<" "<<flight.getSeatMap()[currentRow][i]<<" |";
	}
	std::cout<<std::endl;
	
	std::cout<<"   +";
	for(int i = 0; i < flight.getNumSeats(); i++)
	{
		std::cout<<"---+";
	}
	std::cout<<std::endl;
}

void printCenteredText(int totalTextLength, const std::string& text)
{
	int length = text.size();
	int numSpaces = (totalTextLength - length) / 2;
	for(int i = 0; i <= numSpaces; i++)
	{
		std::cout<<" ";
	}
	std::cout<<text;
	std::cout<<std::endl;
}

void showPassengerInformation(const Flight& f)
{	
	std::cout<<std::left;
	std::cout<<std::setw(20)<<"First Name";
	std::cout<<std::setw(20)<<"Last Name";
	std::cout<<std::setw(20)<<"Phone";
	std::cout<<std::setw(5)<<"Row";
	std::cout<<std::setw(5)<<"Seat";
	std::cout<<std::setw(5)<<"ID"<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl; //75 dashes
	for(int i = 0; i < int(f.getPassengerList().size()); i++)
	{
		std::cout<<std::setw(20)<<f.getPassengerList().at(i).getFirstName();
		std::cout<<std::setw(20)<<f.getPassengerList().at(i).getLastName();
		std::cout<<std::setw(20)<<f.getPassengerList().at(i).getPhoneNumber();
		std::cout<<std::setw(5)<<f.getPassengerList().at(i).getSeat().getRow();
		std::cout<<std::setw(5)<<f.getPassengerList().at(i).getSeat().getSeat();
		std::cout<<std::setw(5)<<f.getPassengerList().at(i).getId()<<std::endl;
		std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	}

	pressReturn();
}
	