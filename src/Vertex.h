/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Vertex.h
Assignment: 5 weighs
Description:	This file holds the Vertex class. The vertex class holds necessary information such as a list of edges that
connect the specific vertex to other vertices. This utilizes an adjacency list.
*/


#include <vector>
#include <string>

#include "Edge.h"

#define BLACK = 2
#define GREY = 1
#define WHITE = 0

class Edge;		//This could potentially fuck everything up, but #YOLO

#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
public:
	//constructor and destructor
	Vertex(int idNum, std::string location);
	~Vertex();

	//assignment operator
	Vertex& operator=(const Vertex& rhs);

	//adds an edge to the vertex
	bool addEdge(Edge* newEdge);
	
	//getters/setters for idNum
	bool setId(int idNum);
	int getId(void) const;

	//getter/setter for name
	bool setName(std::string location);
	std::string getName(void) const;

	//returns a vector with all the edges protruding from this vertex
	std::vector<Edge*> getEdges(void) const;

	//getter/setter for color
	void setColor(int colorNum);
	int getColor(void) const;

	//public member variables
	double distance; //public variable
	Vertex* previousLink;

private:
	int id;
	int color;
	std::string name;
	std::vector<Edge*> edges;
	

};

#endif