/*
Author: Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 05/29/2017
Description: Header file for city class.  Defines a city with id, x coord, and y coord.
Supports relevent getters and setters as well as a distance function to calc distance between 2 cities.
*/

#ifndef CITY_HPP
#define CITY_HPP

class City {
private:
	int id;
	int x;
	int y;

public:
	City();
	City(int id, int x, int y);
	int getID(void);
	int getX(void);
	int getY(void);
	void setID(int);
	void setX(int);
	void setY(int);	
	double distance(City city);
};
#endif