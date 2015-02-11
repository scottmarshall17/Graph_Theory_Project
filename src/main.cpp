/*
	Author: Scott Marshall
	netId: scottmarshall
	Date: 12/10/2014
	File: main.cpp
	Assignment: 5 weighs
	Description:	This program parses a file and creates a graph structured after the guidelines in the file. It then finds the shortest path
		and the most reliable path, which may also be the shortest path. This program takes 3 arguments in the command line.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "Parser.h"


int main(int argc, char* argv[]){
	Graph myGraph;
	std::stringstream myStrStream;
	int srcId = 0;
	int destId = 0;

	//check for the right command arguments
	if (argc != 4){
		std::cout << "Usage: ./weighs <start ID> <end ID> <fileName>" << std::endl;
		return -1;
	}

	std::string myFile(argv[3]);

	//turn the strings into numbers
	myStrStream.clear();
	myStrStream.str(argv[1]);
	myStrStream >> srcId;

	myStrStream.clear();
	myStrStream.str(argv[2]);
	myStrStream >> destId;

	//parse the graph from the file and find the necessary paths.
	if (parseGraphFile(myFile, &myGraph)){

		if (myGraph.findShortestPath(srcId, destId)){
			myGraph.printShortPath(destId);
		}
		if (myGraph.findReliablePath(srcId, destId)){
			myGraph.printReliablePath(srcId, destId);
		}
	}
	
	

	return 0;
}