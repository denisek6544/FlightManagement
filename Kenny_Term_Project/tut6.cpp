//all of these use namespace std
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

//because this is in a header file you need to #ifndef #define
class Point
{
	private:
		double x;
		double y;
		std::string name;
	public:
		//getters and setters inline
		double getx()const {return x;}
		void setx(double value) {x = value;}
		double gety()const {return y;}
		void sety(double value) {y = value;}
		
		
		Point(double xCoor, int yCoor, std::string label): x(xCoor), y(yCoor), name(label) {}
};
//endif

//because this is in a header file you need to #ifndef #define
class Shape
{
	private:
		std::vector<Point> shape; //this creates an object - an empty list
	public:
		void add_point(const Point& x);
		void show_point()const;
};
//endif

void read_points_from_file(str, Shape shape)
{
	//read up to 19th character because there needs to be a space for the /0
	//when you are reading something in your file
	//when you are reading an integer
	//in >> x >> y;
	//the cursor stays at the end of the number.
	//char junk[100];
	//in.getline(junk, 100);
	//or in.get() to get the cursor to go to the next line
	
}