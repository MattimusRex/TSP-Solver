/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  Program that runs christofides algorithm and 2-opt for solving traveling salesman problem
*/
#include "city.hpp"
#include "edge.hpp"
#include "utility.hpp"
#include "christofides.hpp"
#include "twoOpt.hpp"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <stack>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::getline;


int main(int argc, char *argv[]) {
	clock_t start, stop;
	start = clock();
	double totalTime;

	//get input filename from agrv[] or prompt user for input file name
	string inputFilename;
	if (argc > 1) {
		inputFilename = argv[1];
	}
	else {
		cout << "Enter input filename: " << endl;
		getline(cin, inputFilename);
	}
	
	// format output filename
	string outputFilename = inputFilename + ".tour";

	// read input from input file
	vector<City*> cities = readInput(inputFilename);

	// get total number of cities read from input file
	int numOfCities = cities.size();

	// create matrix of distance between each vertex
	vector<vector<int> > edgeMatrix;
	edgeMatrix.resize(numOfCities, vector<int>(numOfCities, 0));
	for (int i = 0; i < edgeMatrix.size(); i++) { // turn cities into an edge matrrx
		for (int j = i; j < edgeMatrix[i].size(); j++) {
			// distance from vertex to itself is 0
			if (j == i)
				edgeMatrix[i][j] = 0;
			// calculate distance from i to j
			// distance from i to j is the same as distance from j to i
			else { 
				edgeMatrix[i][j] = (int)cities[i]->distance(*cities[j]);
				edgeMatrix[j][i] = edgeMatrix[i][j];
			}
		}
	} 

	//turn the edge matrix into a minimum spanning tree
	vector<vector<Edge> > adjListMST = MST(edgeMatrix);

	// make a sub graph of the tree for vertices with an odd degre
	vector<int> odds = vertOddDegree(adjListMST); 
	
	// matching odd vertices to get multigraph with even vertices
	minMatch(adjListMST, odds, edgeMatrix); 

	// find euler tour using multigraph generated starting from first vertex
	vector<int> eulerTour = matchToEuler(adjListMST, adjListMST[0][0].v1);

	// find hamilton tour (TSP solution) using euler tour generated
	vector<int> hamiltonTour = hamilton(eulerTour, numOfCities);
	int hamiltonDistance = tourDistance(hamiltonTour, edgeMatrix);
	cout << "hamilton tour length: " << hamiltonDistance << endl;

	// run 2-opt on TSP tour generated
	vector<int> tour = twoOpt(hamiltonTour, edgeMatrix, hamiltonDistance, start, outputFilename);
	int finalDistance = tourDistance(tour, edgeMatrix);
	cout << "tour length after 2opt: " << finalDistance << endl;

	// write TSP solution to output file
	writeOutput(outputFilename, tour, finalDistance);

	// get total time taken to complete 
	stop = clock();
	totalTime = (double)(stop - start)/CLOCKS_PER_SEC;
	cout << "Total time: " << totalTime << " seconds" << endl;
}


