/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 05/29/2017
Description:  Header file for edge class. Defines an edge with v1, v2, and weight.
*/

#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
public:
	Edge(int v1, int v2, int weight);
	int v1;
	int v2;
	int weight;
	bool removed;

};

#endif