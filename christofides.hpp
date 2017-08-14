/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  Header file for Christofides algorithms
*/
#ifndef CHRISTOFIDES_HPP
#define CHRISTOFIDES_HPP

#include "edge.hpp"
#include <vector>
using std::vector;

vector<vector<Edge> > MST(vector<vector<int> >& edgeMatrix);
int findMin(vector<int>& key); 
vector<int> vertOddDegree(vector<vector<Edge> >& adjList);
void minMatch(vector<vector<Edge> >& graph, vector<int>& oddVertices, vector<vector<int> > em);
vector<int> matchToEuler (vector<vector<Edge> >& graph, int start);
vector<int> hamilton (vector<int> eulerTour, int numOfCities);

#endif
