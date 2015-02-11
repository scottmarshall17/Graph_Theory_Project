/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Edge.h
Assignment: 5 weighs
Description:	This file holds the Edge class. The Edge class holds necessary information such as the adjacent vertex
	it connects to.
*/


#include <vector>

class Vertex;

#ifndef EDGE_H
#define EDGE_H

class Edge{
public:
	//Constructor 
	Edge(Vertex* firstVertex, Vertex* nextVertex, double minTime, double maxTime);

	Edge& operator=(const Edge& rhs);

	//setter and getter for adjVertex
	bool setAdjVertex(Vertex* link);
	Vertex* getAdjVertex(void) const;

	//setter and getter for path
	bool setPath(Vertex* start, Vertex* end);
	std::vector<int> getPath(void) const;

	//setter and getter for minTime
	bool setMinTime(double time);
	double getMinTime(void) const;


	//setter and getter for maxTime
	bool setMaxTime(double time);
	double getMaxTime(void) const;

	//public member variable for traversal purposes.
	bool traveled;

private:
	Vertex* adjVertex;
	std::vector<int> path;
	double minTime;
	double maxTime;

};

#endif