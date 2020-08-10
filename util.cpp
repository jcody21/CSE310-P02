// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#include <stdio.h> // used to get input from the user
#include <fstream> // used to get input from a file
#include "util.h" 
using namespace std;

//#pragma warning(disable:4996) // this is used when compiling in virtual studio (Visual C++), it is unneccessary when using gcc

// reads from the input stream until it gathers a command
int nextCommand(int* s, int* t, int* f) {
	char c; // declaring a variable to use for input

	while (1) {
		scanf("%c", &c); // taking in new input
		if (c == ' ' || c == '\t' || c == '\n') { // discarding whitespace
			continue; }

		if (c == 'S' || c == 's') { // Ends the program
			c = 'S'; // setting a definte value for output
			break; }
		
		if (c == 'R' || c == 'r') { // reads in a graph from a file and then builds the adjacency lists
			c = 'R';
			break; }
		
		if (c == 'W' || c == 'w') { // prints the graph info to the screen
			c = 'W';
			break; }
		
		if (c == 'F' || c == 'f') { // runs Dijkstra's shortest path algorithim and outputs info
			c = 'F';
			scanf("%d", s); // starting vertice
			scanf("%d", t); // ending vertice
			scanf("%d", f); // determines what the output looks like
			break; }

		else {
			c = '\0'; // getting rid of old input
			continue;
		}
		
		//printf("Invalid Command\n"); 
		// "Invalid Command\n" never showed up in any of the tests, so I have omitted it as 
		// I was uncertain that it needed to be in the program. 
	}
	return c;
}


// reads input from a file to generate the edge adjacency list and store the number of vertecies and edges in the graph
// NOTE: the file must hold a positive weighted directed graph in order for the rest of the program to work properly
void fileReader(GRAPH * myGraph, char fileName[]) { 
	ifstream myfile; // creating an ifstream file
	myfile.open(fileName); // opening the file to be read

	if (!myfile.is_open()) { // checking to make sure the file opened
		printf("The file did not open properly.\n"); // letting the user know about the failure and then exiting
		printf("The program is now qutting.\n");
		return;
	}

	int start, end, weight, numVerticies, numEdges; // declaring variables to use for input
	myfile >> numVerticies >> numEdges; // storing the number of verticies and edges
	
	// this input is not sanitized as we should be able to trust this file
	// if we cannot, then this code would need input sanitation

	myGraph->v = numVerticies; // storing the data from the file into the graph
	myGraph->e = numEdges;

	myGraph->H = new ELEMENT[numVerticies + 1]; // creating arrays to hold elements and edges
	myGraph->A = new LIST *[numVerticies + 1]; 

	for (int i = 1; i < numVerticies + 1; i++) { // initializing the arrays 
		myGraph->H[i].node = i;
		myGraph->A[i] = NULL;
	}

	LIST** edges = myGraph->A; // pointers to make editing easier
	LIST* ptr;
	
	for (int i = 1; i < numEdges + 1; i++) {
		myfile >> start >> end >> weight; // taking input on the edges
		ptr = edges[start];
		
		if (ptr == NULL) {
			ptr = new LIST; // creating a new node to store our data
			edges[start] = ptr;

			ptr->neighbor = end; // writing data from the file into the node
			ptr->weight = weight;
			ptr->next = NULL;
		}
		else {
			ptr = new LIST; // creating a new node at the front
			ptr->next = edges[start]; // hooking the rest of the chain to the new top
			edges[start] = ptr; // having the array point to the new top

			ptr->neighbor = end; // storing data
			ptr->weight = weight;
		}
	}

	myfile.close(); // closing the file now that we are finished
}
