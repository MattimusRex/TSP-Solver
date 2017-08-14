/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  Implementation of 2-opt algorithm
*/

#include "twoOpt.hpp"
#include <vector>
#include <string>
#include "utility.hpp"
#include <ctime>
#include <limits>

using std::vector;
using std::string;

/* swap two edges
 * parameters: 	tour - TSP solution
 *				index1 - vertex for swapping
 *				index2 - vertex for swapping
 * return: alters the tour used as parameter
 */
void twoOptSwap(vector<int>& tour, int index1, int index2) {
	int count = (index2 - index1) / 2;
	if (count == 0) {
		count = 1;
	}
	for (int i = 0; i < count; i++) {
		int temp = tour[index1];
		tour[index1] = tour[index2];
		tour[index2] = temp;
		index1++;
		index2--;
	}
}

/* Optimizes TSP solution by swapping two edges and checking if a better tour is obtained
 * after each swap
 * parameters: 	tour - TSP solution
 *				em - matrix of distances between each vertices
 *				initialDistance - distance of tour 
 *				start - current total run time
 *				outputFilename - name of output file
 * return: a better tour
 */
vector<int> twoOpt(vector<int>& tour, vector<vector<int> >& em, int initialDistance, clock_t start, string outputFilename) {
	vector<int> bestTour;
	int bestDistance = initialDistance;

	int found = 1;
	while (found > 0) {
		found = 0;
		for (int i = 0; i < tour.size() - 1; i++) {
			for (int j = i + 1; j < tour.size(); j++) {
				if (double(clock() - start)/CLOCKS_PER_SEC > 175 && double(clock() - start) / CLOCKS_PER_SEC < 177) {
					writeOutput(outputFilename, tour, bestDistance);
				}
				int newDistance = twoOptDist(tour, i, j, em, bestDistance);
				if (newDistance < bestDistance) {
					bestDistance = newDistance;
					twoOptSwap(tour, i, j);
					found++;
				}
			}
		}
	}
	return tour;
}

/* Calculates the distance of a tour after a potential swap at indices i and j
* parameters: 	tour - TSP solution
				i - beginning of swap section
				j - end of swap section
*				em - matrix of distances between each vertices
*				distance - distance of tour
* return: distance of the tour if a swap were to occur with indices i and j
*/
int twoOptDist(vector<int>& tour, int i, int j, vector<vector<int> >& em, int distance) {
	if (i == 0 && j == tour.size() - 1) {
		return distance;
	}
	else if (i == 0) {
		distance -= em[tour[j]][tour[j + 1]] + em[tour[i]][tour.back()];
		distance += em[tour[i]][tour[j + 1]] + em[tour[j]][tour.back()];
	}
	else if (j == tour.size() - 1) {
		distance -= em[tour[i]][tour[i - 1]] + em[tour[j]][tour[0]];
		distance += em[tour[j]][tour[i - 1]] + em[tour[i]][tour[0]];
	}
	else {
		distance -= em[tour[i]][tour[i - 1]] + em[tour[j]][tour[j + 1]];
		distance += em[tour[j]][tour[i - 1]] + em[tour[i]][tour[j + 1]];
	}
	return distance;
}