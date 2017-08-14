/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description: header file for utility functions
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "city.hpp"
#include <string>
#include <vector>
using std::vector;
using std::string;

vector<City*> readInput(string);
void writeOutput(string, vector<int>, int);
int tourDistance(vector<int>& tour, vector<vector<int> > &em);

#endif
