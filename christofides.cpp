/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 06/5/2017
Description:  Implementation of Christofides algorithm
*/
#include "christofides.hpp"
#include "edge.hpp"
#include <vector>
#include <stack>
#include <limits>
using std::vector;
using std::stack;
using std::numeric_limits;

/* Finding minimum spanning tree
 * parameters: edgeMatrix - a matrix of distances between each vertex
 * return: a matrix of adjacency edges list 
 */
vector<vector<Edge> > MST(vector<vector<int> >& edgeMatrix) {
	int numOfCities = edgeMatrix.size();
	vector<vector<Edge> > adjList;
	adjList.resize(numOfCities);
	vector<int> key(numOfCities, numeric_limits<int>::max());
	vector<int> parent(numOfCities);
	key[0] = 0;
	parent[0] = 0;
	for (int i = 0; i < numOfCities; i++) {
		int min = findMin(key);
		key[min] = -1;
		for (int j = 0; j < numOfCities; j++) {
			if (key[j] != -1 && edgeMatrix[min][j] < key[j]) {
				key[j] = edgeMatrix[min][j];
				parent[j] = min;
			}
		}
	}
	for (int i = 1; i < numOfCities; i++) {
		int vertex1 = i;
		int vertex2 = parent[i];
		int weight = edgeMatrix[vertex1][vertex2];
		adjList[vertex1].push_back(Edge(vertex1, vertex2, weight));
		adjList[vertex2].push_back(Edge(vertex2, vertex1, weight));
	}
	return adjList;
}


int findMin(vector<int>& key) {
	int minIndex = -1;
	int min = numeric_limits<int>::max();
	for (int i = 0; i < key.size(); i++) {
		if (key[i] > -1 && key[i] < min) {
			minIndex = i;
			min = key[i];
		}
	}
	return minIndex;
}

/* find vertices of odd degree by checking if # of edges is odd
 * parameters: adjList - a matrix of adjacency edges
 * return: vector of odd vertices
 */
vector<int> vertOddDegree(vector<vector<Edge> >& adjList) {
	vector<int> oddVertices;
	for (int i = 0; i < adjList.size(); i++) {
		if (adjList[i].size() % 2 == 1) {
			oddVertices.push_back(i);
		}
	}
	return oddVertices;
}

/* finds a perfect match of the odd vertices.  its not the minimal match, but its a small match
 * parameters: 	graph - matrix of adjacency edges
 *				oddVertices - list of odd vertices
 *				em - matrix of distances between all vertices
 */
void minMatch(vector<vector<Edge> >& graph, vector<int>& oddVertices, vector<vector<int> > em) {
	//use index to track which odd vertex you're on.  these graphs have an even number of odd vertices
	//and each match removes 2 of the vertices, so we only need to do it #of odd v / 2 times
	//oddVertices is storing the id of the cities.  so graph[oddVertex][j] gives the jth edge of that vertex.
	//v2 of that edge is the vertex that connects to oddVertex via that edge
	int index = 0;
	for (int i = 0; i < oddVertices.size() / 2; i++) {
		//get the next odd vertex, skipping any we have set to the tombstone of -1
		//use tombstone because cant easily delete
		int curVertex = oddVertices[index];
		while (curVertex == -1) {
			index++;
			curVertex = oddVertices[index];
		}
		//set length to inf and then look at the weight of all the edges of curVertex
		//this finds the edge that is the smallest and puts it in the match
		int length = numeric_limits<int>::max();
		int nearestVert = -1;
		int nearVIndex;
		for (int j = 0; j < oddVertices.size(); j++) {
			if (oddVertices[j] != -1 && j != index && em[curVertex][oddVertices[j]] < length) {
				length = em[curVertex][oddVertices[j]];
				nearestVert = oddVertices[j];
				nearVIndex = j;
			}
		}
		oddVertices[index] = -1;
		oddVertices[nearVIndex] = -1;
		graph[curVertex].push_back(Edge(curVertex, nearestVert, length));
		graph[nearestVert].push_back(Edge(nearestVert, curVertex, length));
		index++;
	}
}

/* Find an Euler tour (a tour that uses all the edges exactly once) 
 * from the multigraph obtained after perfect matching. 
 * parameters: 	graph - multigraph of edges
 *				start - starting vertex
 * return: Euler Tour
 */
vector<int> matchToEuler (vector<vector<Edge> >& graph, int start) {   
	stack<Edge> available; 	//stack to hold available edges from vertex1
	stack<int> curPath;		//stack to hold vertices traverse so far
	int numAvai, vertex2, vertex1 = start;
	vector<int> circuit; 	//hold vertices with no more available edges
	curPath.push(vertex1);	//push starting vertex to curPath
	   
    do {
   		// first do-while loop: check if current vertex has any more available edges for traversal
    	do {
    		numAvai = 0; //counter to hold currently available edges from vertex 1

    		//check for available edges
    		//if edge's removed is not marked, add edge to available list
    		//increment numAvai
			for (int i = 0; i < graph[vertex1].size(); i++) {
				if (!graph[vertex1][i].removed){
					available.push(graph[vertex1][i]);
					//cout << "available edge: " << available.top().v1 << "-" << available.top().v2 << endl;
					numAvai++;
				}
			}

			//if current vertex has no remaining un-traverse edge available
			//perform backtracking 
			if (numAvai == 0) {
				// add current vertex to circuit	
				circuit.push_back(vertex1);
				//cout << "***backtracking: " << vertex1 << endl;

				// remove current vertex from list of current path taken
				curPath.pop();

				// if current path is not empty, get the top vertex from stack
				// otherwise set vertex1 to some arbituary number
				if (!curPath.empty()){
					vertex1 = curPath.top();
				}
				else {
					vertex1 = -5;
				}
			}
		// re-iterate the loop if number of available edges is 0 and if curPath is not empty
		} while (numAvai == 0 && !curPath.empty());

		// if vertex1 is some arbitrary number, break out of the second do-while loop
		if (vertex1 == -5) {
			break;
		}

		// otherwise
		else {
			// get edge to traverse from available stack
			Edge* next = &available.top();
			available.pop();

			// set vertex2 
			vertex2 = next->v2;
			//cout << "traversing edge: " << vertex1 << "-" << vertex2 << endl;
			
			// add vertex2 to current path taken
			curPath.push(vertex2);

			// mark the edge as removed
		 	for(int x = 0; x < graph[vertex1].size(); x++) {
		            if(graph[vertex1][x].v2 == vertex2) {
		                    graph[vertex1][x].removed = true; 
		            }
		    }

		    // mark sister edge as removed
		    for(int y = 0; y < graph[vertex2].size(); y++) {
		            if(graph[vertex2][y].v2 == vertex1) {
		                    graph[vertex2][y].removed = true; 
		            }
		    }

		    // set vertex1 to vertex2 for next iteration because want to look for available
		    // edge of vertex2
		    vertex1 = vertex2;
		}	
	// re-iterate until available stack is empty, i.e all edges have been traversed    
    } while (!available.empty());

    // reverse the circuit to get Euler Path
    vector<int> eulerTour;
    for (int i = circuit.size() - 1; i >= 0; i--) {
    	eulerTour.push_back(circuit[i]);
    }

    // return Euler Path
    return eulerTour;
}

/* find a Hamiltonian tour by skipping repeated vertices of the Euler tour generated
 * from matchToEuler()
 * parameters: 	eulerTour - a tour that goes through all edges exactly once
 *				numOfCities - total number of cities in our tour
 * return: Hamilton tour i.e. TSP solution
 */
vector<int> hamilton (vector<int> eulerTour, int numOfCities) {
	//convert euler tour into hamilton cycle
	vector<int> initialTour;
	vector<bool> alreadySeen(numOfCities, 0);
	//alreadySeen[index] will make whether the city whose id is index is already in the final tour
	for (int i = 0; i < eulerTour.size(); i++) {
		if (alreadySeen[eulerTour[i]] == 0) {
			initialTour.push_back(eulerTour[i]);
			alreadySeen[eulerTour[i]] = 1;
		}
	}
	return initialTour;
}

