// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#include <stdio.h> // included for output
#include <limits.h> // included for use in initializeSingleSource() to set to int to the max
#include "graph.h"


// frees memory used by a dynamically allocated GRAPH
void graphDeleter(GRAPH* myGraph) {
	if (myGraph->H != NULL) { // if there were no elements allocated, don't try to delete 
		delete[] myGraph->H; // deleting the array of elements
	}

	if (myGraph->A != NULL) { // if the LIST* array was never allocated, don't try to delete
		LIST** X = myGraph->A; // creating some variables to help navigate the singly linked list
		LIST* current = X[1];
		LIST* next = current;

		for (int i = 1; i <= myGraph->v; i++) { // deleting the contents of the array of list pointers
			current = X[i];

			if (current == NULL) { // if current is blank, we can skip this iteration and go to the next
				continue;
			}

			while (current != NULL) { // looping to delete all of the lists in the singly linked list
				next = current->next; // keeping track of the next list node to delete
				delete current; // deleting the current list node
				current = next; // making the current now point to the next in preparation for the next deletion
			}
			X[i] = NULL; // preventing any unauthorized access of now bad data
		}
		delete[] myGraph->A; // deleting the array of list pointers
	}
	delete myGraph; // deleting everything else (two ints, element pointer, and list pointer)
}

// takes in a GRAPH pointer and prints the number of edges, 
// the number of verticies, and the edge adjacency list
void printGraph(GRAPH* myGraph) {
	LIST* current; // pointer to make access easier
	printf("%d %d\n", myGraph->v, myGraph->e); // printing the number of verticies and edges
	for (int i = 1; i <= myGraph->v; i++) { // printing the edge adjacency list
		current = myGraph->A[i]; // setting the pointer
		printf("%d : ", i); // printing the start element
		
		if (current != NULL) { // checking to make sure there is an edge to print
			printf("(%d, %d)", current->neighbor, current->weight); // printing the first edge
			current = current->next; // incrementing the pointer
		}
		// the print statements are broken up because the print format is slightly different
		while (current != NULL) {// checking to make sure there is an edge to print
			printf("; (%d, %d)", current->neighbor, current->weight); // 2nd to infinite edge print
			current = current->next; // incrementing the pointer
		}
		printf("\n"); // newline on the end
	}
}

// sets all of the verticies in the graph to infinite distance except for the source
void initializeSingleSource(GRAPH* myGraph, int source) {
	for (int i = 1; i < myGraph->v + 1; i++) { // looping through the heap
		myGraph->H[i].d = INT_MAX; // setting the distance to infinite
		myGraph->H[i].p = 0; // setting the predecessor to nothing
	}
	myGraph->H[source].d = 0; // setting the source back to 0
}

// takes in the indexes of the nodes to be relaxed and the edge to use and 
// sets the end to the combined distace if that is less than what the node currently holds
void relax(GRAPH* myGraph, int start, int end, LIST* edge) {
	if (myGraph->H[end].d > myGraph->H[start].d + edge->weight) {
		myGraph->H[end].d = myGraph->H[start].d + edge->weight;
		myGraph->H[end].p = myGraph->H[start].node;
		MinHeapify(myGraph, Parent(end));
	}
}

// calculates the shortest path from the souce to every node
void DijkstraShortestPath(GRAPH* myGraph, int source) {
	initializeSingleSource(myGraph, source); // sets the .d of all of the ELEMENTS to INT_MAX execpt for the source
	
	ELEMENT temp; // declaring temporary variables so I don't have to go through myGraph everytime
	LIST* edge;
	
	const int numVerticies = myGraph->v; // storing the number of verticies as it will be decremented in the myGraph
	
	BuildHeap(myGraph); // creates a min heap in ELEMENT array in myGraph

	for (int i = 1; i <= numVerticies; i++) { // looping through all of the verticies as we extract them
		temp = ExtractMin(myGraph);   // storing the element that was extracted for easy access
		edge = myGraph->A[temp.node]; // resetting the edge on the new vertice that was extracted

		while (edge != NULL) { // looping through each edge connected to the vertice
			int j = findElement(myGraph, edge->neighbor); // finding where the element that has a .d is located in the heap
			if (j != 0) { // if 0, the end element we are looking for is not in the heap, so we go to the next edge
				if (temp.d != INT_MAX) { // we don't want to compare as it will cause an overflow, also this node is not connected to source
					relax(myGraph, myGraph->v + 1, j, edge); // trying to reduce the .d of the end 
				}
			}
			edge = edge->next; // incrementing to the next edge
		}
		BuildHeap(myGraph); // reorgaizing the heap to ensure that it still follows the heap property after elements were reduced
	}
	myGraph->v = numVerticies; // setting the number of verticies back to what it should be
}

// prints the path from the source node to i
void pathPrinter(GRAPH* myGraph, int i) { 
	if (myGraph->H[i].d == 0) { // if the .d is 0, it must be the source
		printf("PATH: %d", i); // printing the source case
	}
	else {
		pathPrinter(myGraph, myGraph->H[i].p); // working towards the source 
		printf(", %d", i); // popping and finally printing the path from the source to i
	}
}