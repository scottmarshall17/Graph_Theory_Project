/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Edge.cpp
Assignment: 5 weighs
Description:	This file holds the Edge class member functions. The Edge class holds necessary information such as the adjacent vertex
it connects to.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "Edge.h"
#include "Vertex.h"

//Constructor 
Edge::Edge(Vertex* firstVertex, Vertex* nextVertex, double minTime, double maxTime){
	this->adjVertex = nextVertex;
	this->path.push_back(firstVertex->getId());
	this->path.push_back(nextVertex->getId());
	this->minTime = minTime;
	this->maxTime = maxTime;
	traveled = false;
}

//Destructor
Edge& Edge::operator=(const Edge& rhs){
	this->adjVertex = rhs.getAdjVertex();
	this->minTime = rhs.getMinTime();
	this->maxTime = rhs.getMaxTime();
	this->path = rhs.getPath();
	this->traveled = rhs.traveled;

	return *this;
}

//setter for adjVertex
bool Edge::setAdjVertex(Vertex* link){
	bool result = true;

	if (link == NULL){
		result = false;
	}
	else{
		this->adjVertex = link;
	}

	return result;
}

//gets the adjecent vertex
Vertex* Edge::getAdjVertex(void) const{
	return this->adjVertex;
}

//sets the path of the edge for reference
bool Edge::setPath(Vertex* start, Vertex* end){
	bool result = true;

	this->path.clear();

	if (start == NULL || end == NULL){
		result = false;
	}
	else{
		this->path.push_back(start->getId());
		this->path.push_back(end->getId());
	}

	return result;
}

//returns the path of the edge
std::vector<int> Edge::getPath(void) const{
	return this->path;
}

//setter for minTime
bool Edge::setMinTime(double time){
	bool result = true;
	this->minTime = time;
	return result;
}

//getter for minTime
double Edge::getMinTime(void) const{
	return this->minTime;
}

//setter for maxTime
bool Edge::setMaxTime(double time){
	bool result = true;
	this->maxTime = time;
	return result;
}

//getter for maxTime
double Edge::getMaxTime(void) const{
	return this->maxTime;
}
