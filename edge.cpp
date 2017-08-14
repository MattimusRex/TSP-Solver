/*
Author:  Matthew Lay, Chermaine Cheang, Gregory Niebanck
Date: 05/29/2017
Description:  Implementation file for the edge class
*/

#include "edge.hpp"

// edge class constructor
Edge::Edge(int v1, int v2, int weight) {
	this->v1 = v1;
	this->v2 = v2;
	this->weight = weight;
	this-> removed = false;
}
