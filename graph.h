// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#pragma once // done so that this file is only ever included once in other files

#include "heap.h"
#include "structs.h"

void graphDeleter(GRAPH* myGraph); 
// deletes a dynamically allocated graph

void printGraph(GRAPH* myGraph);
// takes in a GRAPH pointer and prints the number of edges, 
// the number of verticies, and the edge adjacency list

void initializeSingleSource(GRAPH* myGraph, int source);
// sets all of the verticies in the graph to infinite distance except for the source, sets the predecessor to 0

void relax(GRAPH* myGraph, int start, int end, LIST* edge);
// takes in the indexes of the nodes to be relaxed and the edge to use and 
// sets the end to the combined distace if that is less than what the node currently holds

void DijkstraShortestPath(GRAPH* myGraph, int source);
// calculates the shortest path from the souce to every node

void pathPrinter(GRAPH* myGraph, int i);
// prints the path from the source node to i