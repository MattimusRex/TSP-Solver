/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 05/29/2017
Description:  Implementation file for the city class
*/

#include "city.hpp"
#include <stdio.h>
#include <math.h>

City::City() {
	id = -1;
}

City::City(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

//return city's id
int City::getID() {
	return id;
}

//return city's x-coordinate
int City::getX() {
	return x;
}

//return city's y-coordinate
int City::getY() {
	return y;
}

//calc the distance between calling city and arg city
double City::distance(City b) {
	double xDiffSq = pow((this->getX() - b.getX()), 2);
	double yDiffSq = pow((this->getY() - b.getY()), 2);
	double dist = round(sqrt(xDiffSq + yDiffSq));
	return dist;
}

//set city's id
void City::setID(int id) {
	this->id = id;
}

//set city's x-coordinate
void City::setX(int x) {
	this->x = x;
}

//set city's y-coordinate
void City::setY(int y) {
	this->y = y;
}