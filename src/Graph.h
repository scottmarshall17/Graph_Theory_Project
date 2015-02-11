/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Graph.h
Assignment: 5 weighs
Description:	This file holds the graph class. This is the overarching structure that contains vertices and edges. The graph class
	also holds the necessary functions to find the shortest path and the most reliable path.
*/

#include <vector>
#include <string>
#include "Edge.h"
#include "Vertex.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
public:
	//constructor and destructor
	Graph();
	~Graph();

	//assignment operator
	Graph& operator=(const Graph& rhs);

	//returns true if the Vertex id exists in the graph
	bool findVertex(int idNum);

	//adds and retrieves vertices in the graph
	bool addVertex(int idNum, std::string locationName);
	bool addVertex(Vertex* node);
	Vertex* getVertex(int idNum);
	std::vector<Vertex*> getVertices(void) const;

	//getter/setter for adding and retrieving edges in the graph.
	bool addEdge(int vertex1, int vertex2, double travelMin, double travelMax);
	std::vector<Edge*> getEdges(void) const;

	//functions to find and print the shortest and most reliable paths
	bool findShortestPath(int idStart, int idEnd);
	bool printShortPath(int dest);
	bool findReliablePath(int idStart, int idEnd);
	bool printReliablePath(int src, int dest);

	//helper function to find minimum distance
	int findMinDist();

	//public member variables for quick access
	std::vector<Vertex*> shortestPath;
	std::vector<Vertex*> reliablePath;
	double maxShortestTime;
	double shortestSpread;

private:
	std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;

};

#endif