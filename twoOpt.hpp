/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  2-opt algorithm header file
*/

#ifndef TWOOPT_HPP
#define TWOOPT_HPP

#include <vector>
#include <string>
#include <ctime>
#include <limits>
using std::vector;
using std::string;

void twoOptSwap(vector<int>& tour, int index1, int index2);
vector<int> twoOpt(vector<int>& tour, vector<vector<int> > &em, int initialDistance, clock_t start, string outputFilename);
int twoOptDist(vector<int>& tour, int i, int j, vector<vector<int> >& em, int distance);

#endif
