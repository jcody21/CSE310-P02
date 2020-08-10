// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#pragma once // done so that this file is only ever included once in other files

#include "structs.h" // including structs.h so that GRAPH is recognized as a data type

int nextCommand(int* s, int* t, int* f); 
// reads from the input stream until it gathers a command

void fileReader(GRAPH* myGraph, char fileName[]);
// reads input from a file to generate the edge adjacency list and store the number of vertecies and edges in the graph