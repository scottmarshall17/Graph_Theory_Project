/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Graph.cpp
Assignment: 5 weighs
Description:	This file holds the graph class member function definitions. This is the overarching structure that contains vertices and edges. The graph class
also holds the necessary functions to find the shortest path and the most reliable path.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"

//constructor
Graph::Graph():vertices(0), edges(0){

}

//This function cleans out the majority of the memory. Deletes Edges and Vertices.
Graph::~Graph(){
	unsigned int i = 0;

	for (i = 0; i < vertices.size(); i++){
		delete vertices.at(i);
	}
	for (i = 0; i < edges.size(); i++){
		delete edges.at(i);
	}
	this->vertices.clear();
	this->edges.clear();
}

//assignment operator
Graph& Graph::operator=(const Graph& rhs){
	this->vertices = rhs.vertices;
	this->edges = rhs.edges;

	return *this;
}

//adds a vertex to the graph
bool Graph::addVertex(int idNum, std::string locationName){
	bool result = true;
	Vertex* newVertex = new Vertex(idNum, locationName);
	if (newVertex == NULL){
		result = false;
	}
	else{
		this->vertices.push_back(newVertex);
	}

	return result;
}

//also adds a vertex to a graph
bool Graph::addVertex(Vertex* node){
	bool result = true;
	
	if (node == NULL){
		result = false;
	}
	else{
		this->vertices.push_back(node);
	}

	return result;
}

//returns the list of vertices in the graph
std::vector<Vertex*> Graph::getVertices(void) const{

	return this->vertices;
}

//adds an edge to the graph
bool Graph::addEdge(int vertex1, int vertex2, double travelMin, double travelMax){
	bool result = true;
	unsigned int i = 0;
	Vertex* tempVertex1 = NULL;
	Vertex* tempVertex2 = NULL;
	Edge* newEdge = NULL;
	std::vector<Edge*> tempEdges;


	//get pointers to the vertices of interest
	for (i = 0; i < this->vertices.size(); i++){
		if (this->vertices.at(i)->getId() == vertex1){
			tempVertex1 = this->vertices.at(i);
		}
		if (this->vertices.at(i)->getId() == vertex2){
			tempVertex2 = this->vertices.at(i);
		}
		if ((tempVertex1 != NULL) && (tempVertex2 != NULL)){
			break;
		}
	}
	//check to see if the vertices were found
	if ((tempVertex1 == NULL) || (tempVertex2 == NULL)){
		result = false;
	}
	else{
		tempEdges = tempVertex1->getEdges();
		for (i = 0; i < tempEdges.size(); i++){
			if ( tempEdges.at(i)->getAdjVertex() == tempVertex2){
				result = false;
			}
		}

		if (result != false){
			//create a new Edge and add it to the graph and vertex objects
			newEdge = new Edge(tempVertex1, tempVertex2, travelMin, travelMax);
			if (newEdge == NULL){
				result = false;
			}
			else{
				tempVertex1->addEdge(newEdge);
				this->edges.push_back(newEdge);
			}
		}
	}

	return result;
}

//returns a vector of edges within the graph
std::vector<Edge*> Graph::getEdges(void) const{
	return this->edges;
}

//looks for a Vertex with the passed in Id number. returns true if found.
bool Graph::findVertex(int idNum){
	bool result = false;
	unsigned int i = 0;
	for (i = 0; i < this->vertices.size(); i++){
		if (this->vertices.at(i)->getId() == idNum){
			result = true;
			break;
		}
	}

	return result;
}

//returns a pointer to the vertex with the specified Id
Vertex* Graph::getVertex(int idNum){
	unsigned int i = 0;
	Vertex* result = NULL;

	for (i = 0; i < this->vertices.size(); i++){
		if (this->vertices.at(i)->getId() == idNum){
			result = this->vertices.at(i);
			break;
		}
	}

	return result;
}

//finds the shortest path from the start vertex
bool Graph::findShortestPath(int idStart, int idEnd){
	bool result = true;
	Vertex* myVertex;
	int vertexId = 0;
	std::vector<Edge*> myEdges;
	Edge* singleEdge;

	for (unsigned int i = 0; i < vertices.size(); i++){
		vertices.at(i)->setColor(0);
		vertices.at(i)->distance = pow(10, 100);
		vertices.at(i)->previousLink = NULL;
	}

	if (!(this->findVertex(idStart)) || !(this->findVertex(idEnd))){
		std::cout << "The id was not found in the graph" << std::endl;
		result = false;
	}
	else{
		myVertex = this->getVertex(idStart);
		myVertex->distance = 0;

		for (unsigned int i = 0; i < vertices.size(); i++){
			//myVertex = the minimum distance
			vertexId = this->findMinDist();
			myVertex = this->getVertex(vertexId);
			myVertex->setColor(2);

			myEdges = myVertex->getEdges();

			for (unsigned int j = 0; j < myEdges.size(); j++){
				singleEdge = myEdges.at(j);

				if (((singleEdge->getAdjVertex())->getColor() != 2) && ((singleEdge->getAdjVertex()->distance) >= (myVertex->distance + singleEdge->getMinTime()))){
					singleEdge->getAdjVertex()->distance = (myVertex->distance + singleEdge->getMinTime());
					singleEdge->getAdjVertex()->previousLink = myVertex;
				}
			}

		}
	}


	return result;
}

//helper function that finds the next vertex with the least distance from the source.
int Graph::findMinDist(){
	int result = 0;
	double minVal = pow(10, 100);

	for (unsigned int i = 0; i < vertices.size(); i++){
		if ((vertices.at(i)->distance <= minVal) && (vertices.at(i)->getColor() != 2)){
			minVal = vertices.at(i)->distance;
			result = vertices.at(i)->getId();
		}
	}

	return result;
}

//prints out the shortest path
bool Graph::printShortPath(int dest){
	bool result = true;
	std::vector<Vertex*> myPath;
	Vertex* myVertex;
	double minTime = 0;
	double maxTime = 0;
	std::vector<Edge*> myLinks;

	if (!(this->findVertex(dest))){
		std::cout << "No routes found." << std::endl;
		result = false;
	}
	else{
		myVertex = this->getVertex(dest);
		if (myVertex->distance == pow(10, 100)){
			std::cout << "No routes found." << std::endl;
			result = false;
		}
		else{
			myPath.push_back(myVertex);
			while (myVertex->previousLink != NULL){
				myVertex = myVertex->previousLink;
				myPath.push_back(myVertex);
			}
			for (int c = myPath.size() - 1; c >= 0; c--){
				myVertex = myPath.at(c);
				myLinks = myVertex->getEdges();
				for (std::vector<Edge*>::iterator it = myLinks.begin(); it != myLinks.end(); it++){
					if ((c != 0) && ((*it)->getAdjVertex() == myPath.at(c - 1))){
						minTime = minTime + (*it)->getMinTime();
						maxTime = maxTime + (*it)->getMaxTime();
						break;
					}
				}
				
			}

			std::cout << "Shortest path: " << myPath.at(myPath.size() - 1)->getId() << " to " << myPath.at(0)->getId() << " (" << minTime << " to " << maxTime << ")" << std::endl;
			for (int c = myPath.size() - 1; c >= 0; c--){
				std::cout << " " << myPath.at(c)->getName() << std::endl;
			}
		}
	}
	this->shortestSpread = maxTime - minTime;
	this->shortestPath = myPath;
	this->maxShortestTime = maxTime;
	return result;
}

//finds the most reliable path.
bool Graph::findReliablePath(int idStart, int idEnd){
	bool result = true;
	Vertex* myVertex;
	int vertexId = 0;
	std::vector<Edge*> myEdges;
	Edge* singleEdge;
	Edge* tempEdge;
	double tempTime1 = 0;
	double tempTime2 = 0;
	double averageDist = 0;

	if (shortestPath.size() > 0 && shortestPath.at(0)->previousLink != NULL){
		myEdges = shortestPath.at(0)->previousLink->getEdges();
		for (unsigned int i = 0; i < myEdges.size(); i++){
			if (myEdges.at(i)->getAdjVertex() == shortestPath.at(0)){
				tempEdge = myEdges.at(i);
				tempTime1 = myEdges.at(i)->getMinTime();
				tempTime2 = myEdges.at(i)->getMaxTime();
				myEdges.at(i)->setMinTime(pow(10, 100));
				myEdges.at(i)->setMaxTime(pow(10, 100));
				break;
			}
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++){
		vertices.at(i)->setColor(0);
		vertices.at(i)->distance = pow(10, 100);
		vertices.at(i)->previousLink = NULL;
	}

	if (!(this->findVertex(idStart)) || !(this->findVertex(idEnd))){
		std::cout << "The ID was not found in the graph" << std::endl;
		result = false;
	}
	else{
		myVertex = this->getVertex(idStart);
		myVertex->distance = 0;

		for (unsigned int i = 0; i < vertices.size(); i++){
			//myVertex = the minimum distance
			vertexId = this->findMinDist();
			myVertex = this->getVertex(vertexId);
			myVertex->setColor(2);

			myEdges = myVertex->getEdges();

			for (unsigned int j = 0; j < myEdges.size(); j++){
				singleEdge = myEdges.at(j);
				averageDist = (singleEdge->getMaxTime() + singleEdge->getMinTime()) / 2;

				if (((singleEdge->getAdjVertex())->getColor() != 2) && ((singleEdge->getAdjVertex()->distance) >= myVertex->distance + singleEdge->getMinTime())){
					//singleEdge->getAdjVertex()->distance = (myVertex->distance + (averageDist));
					singleEdge->getAdjVertex()->distance = (myVertex->distance + (singleEdge->getMaxTime() - singleEdge->getMinTime()));
					singleEdge->getAdjVertex()->previousLink = myVertex;
				}
			}

		}
		
		if (shortestPath.size() > 1 && shortestPath.at(0)->previousLink != NULL){
			tempEdge->setMinTime(tempTime1);
			tempEdge->setMaxTime(tempTime2);
		}

	}


	return result;
}

//prints out the most reliable path
bool Graph::printReliablePath(int src, int dest){
	bool result = true;
	std::vector<Vertex*> myPath;
	Vertex* myVertex;
	double minTime = 0;
	double maxTime = 0;
	std::vector<Edge*> myLinks;

	if (!(this->findVertex(dest))){
		std::cout << "No routes found." << std::endl;
		result = false;
	}
	else{
		myVertex = this->getVertex(dest);
		if (myVertex->distance == pow(10, 100)){
			std::cout << "No routes found." << std::endl;
			result = false;
		}
		else{
			myPath.push_back(myVertex);
			while (myVertex->previousLink != NULL){
				myVertex = myVertex->previousLink;
				myPath.push_back(myVertex);
			}
			for (int c = myPath.size() - 1; c >= 0; c--){
				myVertex = myPath.at(c);
				myLinks = myVertex->getEdges();
				for (std::vector<Edge*>::iterator it = myLinks.begin(); it != myLinks.end(); it++){
					if ((c != 0) && ((*it)->getAdjVertex() == myPath.at(c - 1))){
						minTime = minTime + (*it)->getMinTime();
						maxTime = maxTime + (*it)->getMaxTime();
						break;
					}
				}

			}
			this->reliablePath = myPath;
			if ((maxShortestTime > minTime) && ((maxTime - minTime) <= this->shortestSpread)){
				std::cout << "Most reliable path: " << myPath.at(myPath.size() - 1)->getId() << " to " << myPath.at(0)->getId() << " (" << minTime << " to " << maxTime << ")" << std::endl;
				for (int c = myPath.size() - 1; c >= 0; c--){
					std::cout << " " << myPath.at(c)->getName() << std::endl;
				}
			}
			else{
				this->findShortestPath(src, dest);
				this->printShortPath(dest);
			}
			
		}
	}

	return result;
}