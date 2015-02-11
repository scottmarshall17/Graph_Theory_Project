/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Parser.cpp
Assignment: 5 weighs
Description:	This file holds definitions for the file parsing functions in the program.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Edge.h"
#include "Graph.h"
#include "Parser.h"
#include "Vertex.h"

//This function takes a graph and a file and modifies the graph with the file contents 
//of the graph file. returns true if no errors occur.
bool parseGraphFile(std::string fileName, Graph* myGraph){
	bool result = true;
	std::ifstream inFile;
	std::string stringCheck = "";
	std::string tempString = "";
	std::stringstream buffer("");
	std::string location = "";
	std::string tempLocation = "";
	std::vector<Vertex*> vertices;
	Vertex* tempVertex;
	int tempId = 0;
	int node1 = 0;
	int node2 = 0;
	double min = 0;
	double max = 0;
	bool foundWaypoint = false;
	bool foundId = false;
	bool foundStreets = false;
	
	inFile.open(fileName.c_str());	//open the file
	if (!inFile.is_open()){
		result = false;
		std::cout << "Could not find file: " << fileName << std::endl;	//print an error
		return false;
	}
	else{
		std::getline(inFile, tempString);		//get a line from the file
		while (!inFile.eof()){
			buffer.clear();
			buffer.str(tempString);
			if (tempString.compare("") == 0){		//check to make sure the file contents check out okay
				std::getline(inFile, tempString);
				continue;
			}
			if (tempString.compare(stringCheck) == 0){
				break;
			}
			if ((tempString.compare("WAYPOINTS:") == 0)){
				foundWaypoint = true;
				std::getline(inFile, tempString);
				continue;
			}
			if (tempString.compare("STREETS:") == 0){
				if(foundWaypoint == true){
					foundStreets = true;
					break;
				}
				else{
					return false;
				}
			}
			if (foundWaypoint != true){
				std::getline(inFile, tempString);
				continue;
			}

			buffer >> tempId;
			buffer.ignore();
			std::getline(buffer, location);
			vertices = myGraph->getVertices(); //get the list of vertices.

			//this version below uses the iterator to do its dirty work
			for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){			//search for the id of a vertex
				tempVertex = *it;
				if (tempVertex->getId() == tempId){
					std::cout << "Failed: Duplicate ID found" << std::endl;
					inFile.close();
					return false;
				}
			}


			for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){			//search for id of vertex
				if (location.compare((*it)->getName()) == 0){
					std::cout << "Failed: Duplicate location found" << std::endl;
					inFile.close();
					return false;
				}
			}

			myGraph->addVertex(tempId, location);		//add a vertex to the graph
			stringCheck = tempString;

			std::getline(inFile, tempString);

		}
		if (foundStreets == false){
			std::cout << "No streets were listed in the file" << std::endl;
			inFile.close();
			return false;
		}
		
		//now add the edges to the graph
		while (!inFile.eof()){
			std::getline(inFile, tempString);
			buffer.clear();
			buffer.str(tempString);
			if (tempString.compare("") == 0){
				continue;
			}
			if (tempString.compare(stringCheck) == 0){
				break;
			}

			min = -1;
			max = -1;
			node1 = -1;
			node2 = -1;
			buffer >> node1;
			buffer >> node2;
			buffer >> min;
			buffer >> max;

			if ((node1 < 0) || (node2 < 0)){
				std::cout << "Failed: ID numbers cannot be negative" << std::endl;
				inFile.close();
				return false;
			}

			vertices = myGraph->getVertices();
			foundId = false;
		
			//the way of the iterators
			for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){		//find an id number
				if ((*it)->getId() == node1){
					foundId = true;
					break;
				}
			}

			if(foundId == false){
				std::cout << "Failed: can't create an edge to a nonexistant node..." <<std::endl;
				inFile.close();
				return false;
			}
			foundId = false;

			for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){		//find an id number
				if ((*it)->getId() == node2){
					foundId = true;
					break;
				}
			}

			if(foundId == false){
				std::cout << "Failed: can't create an edge to a nonexistant node..." <<std::endl;
				inFile.close();
				return false;
			}

			if((min > max) || (min < 0) || (max < 0)){
				std::cout << "Failed: min/max mismatch" << std::endl;
				result = false;
				inFile.close();
				return false;
			}
			else{
				if (myGraph->addEdge(node1, node2, min, max)){
					stringCheck = tempString;
				}
				else{
					std::cout << "Failed: Error creating edge between nodes" << std::endl;
					result = false;
				}
			}
		}

	}

	if (foundWaypoint == false){
		std::cout << "Failed: Data missing from file" << std::endl;
		result = false;
	}
	if ((myGraph->getVertices().size() == 0)){
		std::cout << "Failed: Data missing from file" << std::endl;
		result = false;
	}
	inFile.close();			//close the file

	return result;
}