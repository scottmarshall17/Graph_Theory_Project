/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Vertex.cpp
Assignment: 5 weighs
Description:	This file holds the Vertex class member function definitions. The vertex class holds necessary information such as a list of edges that
connect the specific vertex to other vertices. This utilizes an adjacency list.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include "Edge.h"
#include "Vertex.h"

//constructor
Vertex::Vertex(int idNum, std::string location)
	:id(idNum), color(0), name(location), edges(0)
{
	this->distance = pow(10, 100);
	this->previousLink = NULL;
}

//destructor
Vertex::~Vertex(){

}

//assignment operator
Vertex& Vertex::operator=(const Vertex& rhs){
	this->id = rhs.getId();
	this->color = rhs.getColor();
	this->name = rhs.getName();
	this->edges = rhs.getEdges();
	this->distance = rhs.distance;

	return *this;
}

//adds an edge to the vertex
bool Vertex::addEdge(Edge* newEdge){
	bool result = true;

	if (newEdge == NULL){
		result = false;
	}
	else{
		this->edges.push_back(newEdge);
	}

	return result;
}

//setter for idNum
bool Vertex::setId(int idNum){
	bool result = true;

	if (idNum < 0){
		result = false;
	}
	else{
		this->id = idNum;
	}

	return result;
}

//getter for idNum
int Vertex::getId(void) const{

	return this->id;
}

//setter for name
bool Vertex::setName(std::string location){
	bool result = true;
	
	this->name = location;

	return result;
}

//getter for name
std::string Vertex::getName(void) const{

	return this->name;
}

//gets the list of edges linked from the vertex
std::vector<Edge*> Vertex::getEdges(void) const{
	return this->edges;
}

//setter for color
void Vertex::setColor(int colorNum){
	
	this->color = colorNum;

	return;
}

//getter for color
int Vertex::getColor(void) const{
	return this->color;
}