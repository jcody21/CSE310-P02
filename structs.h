// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#pragma once  // done so that this file is only ever included once in other files

// holds each of the vertices 
struct ELEMENT {
	int node;	// name of the vertex
	int d;		// distance from the source
	int p;		// predecessor in the path from the source = the .node
};

// structure that holds each of the edges
struct LIST {
	int neighbor;		// the element that the edge connects to
	int weight;			// the weight of the edge
	struct LIST* next;	// a pointer to the next edge that has the same start
};

// the backbone of the entire project
struct GRAPH {
	int v;				// # of verticies
	int e;				// # of edges
	struct ELEMENT* H;	// an array that is used to create a min heap 
	struct LIST** A;	// an array where the index correlates to the start of the edge 
						// & then in each position there is a singly linked list
};