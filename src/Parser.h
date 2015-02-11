/*
Author: Scott Marshall
netId: scottmarshall
Date: 12/10/2014
File: Parser.h
Assignment: 5 weighs
Description:	This file holds prototypes for the file parsing functions in the program.
*/


#include <string>
#include "Graph.h"

#ifndef PARSER_H
#define PARSER_H

//This function takes a graph and a file and modifies the graph with the file contents 
//of the graph file. returns true if no errors occur.
bool parseGraphFile(std::string fileName, Graph* myGraph);

#endif