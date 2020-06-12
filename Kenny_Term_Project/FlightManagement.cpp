#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Flight.h"
#include <vector>
#include "Seat.h"

#define TEXTFILENAME "Flight_Information.txt"

void displayInitialMessage();
void displayOptions();
char selectOption();
void printRows(int numSeats, int currentRow);
Flight readTextFile();
void writeTextFile(Flight& f);
void displayAircraftSeatMap(Flight& flight);
void printRows(Flight& f, int currentRow);
void printCenteredText(int totalTextLength, std::string& text);
void showPassengerInformation(Flight& f);
void print76DashesInALine();
void cleanStandardInputStream();
void pressReturn();
void addPassenger(Flight& flight);
void removePassenger(Flight& flight);
int checkIfNameIsValid(std::string& name);
void removeExcessSpaces(std::string& str);
void formatPhoneNumber(std::string& phoneNum);
int checkIfPhoneNumberIsValid(const std::string& phoneNum);
int isSeatInvalid(const Flight& flight, char seat);
int isRowInvalid(const Flight& flight, int row);
int isSeatTaken(const Flight& flight, int row, char seat);
int isIdTaken(const Flight& flight, int id);

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
	int id;
	std::cout<<"Please enter the passenger id: ";
	std::cin>>id;
	while((!std::cin.good()) || isIdTaken(flight, id))
	{
		if(isIdTaken(flight, id))
			std::cout<<"That id is taken. Please choose another id"<<std::endl;
		else if(!std::cin.good())
		{
			std::cout<<"That is not a valid id. Please try again"<<std::endl;
			cleanStandardInputStream();
		}
		std::cout<<"Please enter the passenger id: ";
		std::cin>>id;
		std::cout<<std::endl;
	}
	
	std::string firstName;
	std::cout<<"Please enter the passenger first name: ";
	cleanStandardInputStream();
	getline(std::cin, firstName, '\n');
	while(!checkIfNameIsValid(firstName))
	{
		std::cout<<"That is not a valid first name. Please try again"<<std::endl;
		std::cout<<"Please enter the passenger first name: ";
		getline(std::cin, firstName, '\n');
		std::cout<<std::endl;
	}
	
	std::string lastName;
	std::cout<<"Please enter the passenger last name: ";
	getline(std::cin, lastName, '\n');
	while(!checkIfNameIsValid(lastName))
	{
		std::cout<<"That is not a valid first name. Please try again"<<std::endl;
		std::cout<<"Please enter the passenger last name: ";
		getline(std::cin, lastName, '\n');
		std::cout<<std::endl;
	}
	
	std::string phoneNumber;
	std::cout<<"Please enter the passenger's phone number: ";
	getline(std::cin, phoneNumber, '\n');
	std::cout<<std::endl;
	while(!checkIfPhoneNumberIsValid(phoneNumber))
	{
		std::cout<<"That is not a valid phone number. Please try again"<<std::endl;
		std::cout<<"Please enter the passenger's phone number: ";
		getline(std::cin, phoneNumber, '\n');
		std::cout<<std::endl;
	}
	formatPhoneNumber(phoneNumber);
	
	int row;
	char seat;
	std::cout<<"Please enter the passenger's desired row: ";
	std::cin>>row;
	std::cout<<"Please enter the passenger's desired seat: ";
	std::cin>>seat;
	while((isSeatInvalid(flight, seat)) || (isRowInvalid(flight, row)) || (isSeatTaken(flight, row, seat)))
	{
		if(isSeatInvalid(flight, seat))
			std::cout<<"That seat is not valid. Please try again."<<std::endl;
		if(isRowInvalid(flight, row))
			std::cout<<"That row is not valid. Please try again."<<std::endl;
		if(isSeatTaken(flight, row, seat))
			std::cout<<"That seat is taken. Please try again."<<std::endl;
		std::cout<<"Please enter the passenger's desired row: ";
		std::cin>>row;
		std::cout<<"Please enter the passenger's desired seat: ";
		std::cin>>seat;
	}
	
	flight.addPassenger(Passenger(firstName, lastName, phoneNumber, Seat(row, seat), id));
	
	cleanStandardInputStream();
	pressReturn();
}

int isSeatInvalid(const Flight& flight, char seat)
{
	if(seat > (flight.getNumSeats() + 'A' - 1))
		return 1;
	return 0;
}

int isRowInvalid(const Flight& flight, int row)
{
	if(row > flight.getNumRows())
		return 1;
	return 0;
}

int isSeatTaken(const Flight& flight, int row, char seat)
{
	if(flight.getSeatMap()[row - 1][seat - 'A'] == 'X')
		return 1;
	return 0;
}

int isIdTaken(const Flight& flight, int id)
{
	for(int i = 0; i < flight.getSizeOfPassengerList(); i++)
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
	while(str.at(0) == ' ')
	{
		str.erase(0, 1);
	}
	
	while(str.at(str.size() - 1) == ' ')
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

int checkIfNameIsValid(std::string& name)
{
	removeExcessSpaces(name);
	if(name.size() > 19)
		return 0;
	return 1;
}

void removePassenger(Flight& flight)
{
	int id;
	std::cout<<"Please enter the id of the passenger that needs to be removed: ";
	std::cin>>id;
	while((!std::cin.good()) || (!flight.removePassenger(id)))
	{
		if(!std::cin.good())
		{
			std::cout<<"That is not a valid id. Please try again";
			cleanStandardInputStream();
		}
		else if(!flight.removePassenger(id))
			std::cout<<"A passenger with that id does not exist. Please try again";
		std::cout<<"Please enter the id of the passenger that needs to be removed: ";
		std::cin>>id;
	}
	cleanStandardInputStream();
	pressReturn();
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
	char ch = 0;
	displayOptions();
	std::cin>>ch;
	while(!((ch >= '1') && (ch <= '6')))
	{
		cleanStandardInputStream();
		std::cout<<"That input is not valid. Please try again"<<std::endl;
		std::cout<<"Enter your choice: (1, 2, 3, 4, 5, or 6) ";
		std::cin>>ch;
	}
	std::cout<<std::endl;
	return ch;
}
	
void cleanStandardInputStream()
{
	std::cin.clear();
	int leftover;
	do
	{
		leftover = std::cin.get();
	}while((leftover!='\n')&&(leftover!=EOF));
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
	std::cout<<"Enter your choice: (1, 2, 3, 4, 5, or 6) ";
}

Flight readTextFile()
{
	std::ifstream inputStream(TEXTFILENAME);
	if(inputStream.fail())
	{
		std::cout<<"Opening the flight information text file failed. This program will now terminate";
		exit(1);
	}
	
	char c = inputStream.get();
	std::string flightName("");
	
	while((c == ' ') || (c == '\n') || (c == '	'))
	{
		c = inputStream.get();
	}
	
	do
	{
		flightName.push_back(c);
		c = inputStream.get();
	} while((c != ' ') && (c!= '\n') && (c!= '	'));
	
	
	int rows;
	int seats;
	
	inputStream>>rows;
	
	inputStream>>seats;

	Flight flight(rows, seats, flightName);
	
	while(!inputStream.eof())
	{
		std::string firstName;
		std::string lastName;
		std::string phoneNumber;
		int id;
		
		while((c == ' ') || (c == '\n') || (c == '	'))
		{
			c = inputStream.get();
		}
		
		do
		{
			firstName.push_back(c);
			c = inputStream.get();
		} while((c != ' ') && (c!= '\n') && (c!= '	'));
		
		while((c == ' ') || (c == '\n') || (c == '	'))
		{
			c = inputStream.get();
		}
		
		do
		{
			lastName.push_back(c);
			c = inputStream.get();
		} while((c != ' ') && (c!= '\n') && (c!= '	'));
		
		while((c == ' ') || (c == '\n') || (c == '	'))
		{
			c = inputStream.get();
		}
		
		do
		{
			phoneNumber.push_back(c);
			c = inputStream.get();
		} while((c != ' ') && (c!= '\n') && (c!= '	'));
		
		int i;
		
		inputStream>>i;
		c = inputStream.get();
		
		Seat seat(i, c);
		
		inputStream>>id;
	
		flight.addPassenger(Passenger(firstName, lastName, phoneNumber, seat, id));
		
		c = inputStream.get();
		
		while((c == ' ') || (c == '\n') || (c == '	'))
		{
			c = inputStream.get();
		}
	}
	
	inputStream.close();
	return flight;
	
}

void writeTextFile(Flight& f)
{
	char ch = 0;
	do
	{
		cleanStandardInputStream();
		std::cout<<"Do you want to save the data in \"Flight_Information.txt\"?"<<std::endl;
		std::cout<<"Please answer <Y or N>: ";
		ch = getchar();
		if(ch == 'Y')
			break;
		else if(ch == 'N')
		{
			pressReturn();
			return;
		}
		else
			std::cout<<"That input is not valid. Please try again"<<std::endl;
	}while(1);
	std::ofstream outputStream(TEXTFILENAME);
	if(outputStream.fail())
	{
		std::cout<<"Opening the flight information text file failed. This program will now terminate";
		exit(1);
	}
	
	outputStream<<std::left<<std::setw(10)<<f.getFlightNumber();
	outputStream<<std::setw(6)<<f.getNumRows();
	outputStream<<std::setw(6)<<f.getNumSeats()<<std::endl;
	
	for(int i = 0; i < f.getSizeOfPassengerList(); i++)
	{
		outputStream<<std::setw(20)<<f.getPassengerList().at(i).getFirstName()<<" ";
		outputStream<<std::setw(20)<<f.getPassengerList().at(i).getLastName()<<" ";
		outputStream<<std::setw(16)<<f.getPassengerList().at(i).getPhoneNumber()<<" ";
		outputStream<<std::setw(1)<<f.getPassengerList().at(i).getSeat().getRow();
		outputStream<<std::setw(1)<<f.getPassengerList().at(i).getSeat().getSeat()<<" ";
		outputStream<<std::setw(8)<<f.getPassengerList().at(i).getId()<<std::endl;
	}
	
	outputStream.close();
	std::cout<<std::endl;
	std::cout<<"All the data in the passenger list was saved into \"Flight_Information.txt\"?"<<std::endl;
	cleanStandardInputStream();
	pressReturn();
}

void displayAircraftSeatMap(Flight& flight)
{
	std::cout << std::left;
	
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
	
	cleanStandardInputStream();
	pressReturn();
}

void printRows(Flight& flight, int currentRow)
{
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

void printCenteredText(int totalTextLength, std::string& text)
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

void showPassengerInformation(Flight& f)
{	
	std::cout<<std::left;
	std::cout<<std::setw(21)<<"First Name";
	std::cout<<std::setw(21)<<"Last Name";
	std::cout<<std::setw(16)<<"Phone";
	std::cout<<std::setw(5)<<"Row";
	std::cout<<std::setw(5)<<"Seat";
	std::cout<<std::setw(8)<<"ID"<<std::endl;
	print76DashesInALine();
	for(int i = 0; i < f.getSizeOfPassengerList(); i++)
	{
		std::cout<<std::setw(21)<<f.getPassengerList().at(i).getFirstName();
		std::cout<<std::setw(21)<<f.getPassengerList().at(i).getLastName();
		std::cout<<std::setw(16)<<f.getPassengerList().at(i).getPhoneNumber();
		std::cout<<std::setw(5)<<f.getPassengerList().at(i).getSeat().getRow();
		std::cout<<std::setw(5)<<f.getPassengerList().at(i).getSeat().getSeat();
		std::cout<<std::setw(8)<<f.getPassengerList().at(i).getId()<<std::endl;
		print76DashesInALine();
	}
	cleanStandardInputStream();
	pressReturn();
}

void print76DashesInALine()
{
	std::cout<<"----------------------------------------------------------------------------"<<std::endl;
}
	


	