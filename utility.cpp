/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  Implementation of utility functions such as reading input, writing output
and getting tour distance
*/


#include "utility.hpp"
#include "city.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

/* 1. read input from input file
 * 2. create a new city object for each line of input
 * 3. add city to vector
 * 4. return vector created
 */
vector<City*> readInput(string inputFilename) {
	//open input file
	ifstream inputFD;
	inputFD.open(inputFilename.c_str());

	vector<City*> cities;
	string line;

	//check if file opened successfully
	if (inputFD.is_open()) {
		int id, x, y;

		while (getline(inputFD, line)){
			stringstream ss(line);
			ss >> id >> x >> y;
			
			//create City object for each id, x, y read in
			City *city = new City(id, x, y);
			//add City object created to vector
			cities.push_back(city);
		}
		
		//close input file when eof reached
		inputFD.close();

	}
	//return vector of cities created
	return cities;
}

/* 1. open/create output file
 * 2. write total tour length to file (distance)
 * 3. write out the path taken
 * 4. close the output file
 */
void writeOutput(string outputFilename, vector<int> cities, int distance) {
	//open output file
	ofstream outputFD (outputFilename.c_str());

	//check if file opened successfully
	if (outputFD.is_open()) {
		//write distance travelled
		outputFD << distance << endl;
		//write path taken
		for (int i = 0; i < cities.size(); i++) {
			outputFD << cities[i] << endl;
		}
		//close file
		outputFD.close();
	}
}

/* calculate TSP solution distance
 * parameters: 	tour - TSP solution
 *				em - matrix of distances between vertices
 * return: tour distance
 */
int tourDistance(vector<int>& tour, vector<vector<int> > &em) {
	int distance = 0;
	for (int i = 0; i < tour.size() - 1; i++) {
		distance += em[tour[i]][tour[i + 1]];
	}
	distance += em[tour[0]][tour.back()];
	return distance;
}
