// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#include <stdio.h>  // included to be used for output
#include <limits.h> // included for comparison in case "F"

#include "heap.h"  // giving main.cpp access to all the other functions/structs
#include "util.h"
#include "graph.h"
#include "structs.h"

char INPUT_FILE[] = "Ginput.txt"; // sets the file to be used as input, can be easily changed

int main() {
	char c; // variables for the parser
	int s, t, iFlag;
	GRAPH *myGraph = NULL; // the GRAPH pointer that will be used throughout

	while (1) { // loop until the "S" command is called to end the program
		c = nextCommand(&s, &t, &iFlag); // waiting for the next piece of input
		switch (c) {
		case 'S': { // ending the program
			printf("COMMAND: %c\n", c); // printing the command
			if (myGraph != NULL) { // if the graph was never initialized, don't try to delete it
				graphDeleter(myGraph); // deleting the graph
			}
			return 0; // exiting the while loop and ending the program
		}

		case 'R': { // reads a file and creates the edge adjacency list 
			printf("COMMAND: %c\n", c); // printing the command
			myGraph = new GRAPH; // creating a graph to store the edge adjacency list
			fileReader(myGraph, INPUT_FILE); // writing the input from the file into the edge adjacency list in the graph
			break;
		}

		case 'W': { // printing the graph and some info about it
			printf("COMMAND: %c\n", c); // printing the command
			if (myGraph == NULL) { // don't print the graph if it hasn't been initialized
				printf("Error: graph not initialized\n");
				break;
			}
			printGraph(myGraph); // printing the graph
			break;
		}

		case 'F': { // calculates and outputs the shortest path/distance from s to t depending on iFlag(0/1)
			printf("COMMAND: %c %d %d %d\n", c, s, t, iFlag); // printing the command
			if (myGraph == NULL) { // if the graph has not been initialized, we don't want to do anything
				printf("Error: graph not initialized\n");
				break;
			}

			// if the command is trying to access either start or end that is outside the acceptable area, 
			// then throw an error and prevent from going further
			if ((s > myGraph->v) || (s < 1) || (t > myGraph->v) || (t < 1)) { 
				printf("Error: one or more invalid nodes\n");
				if (iFlag != 0 && iFlag != 1) {
					printf("Error: invalid flag value\n");
				}
				break;
			}

			if (iFlag != 0 && iFlag != 1) { // if the flag input is bad, exit the command
				printf("Error: invalid flag value\n");
				break;
			}

			DijkstraShortestPath(myGraph, s); // calculating all of the shortest paths
			reorder(myGraph); // reorgainzing the graph for easier access
			  
			if (myGraph->H[t].d == INT_MAX) { // if the distance is essentially infinte, then it is unreachable
				printf("Error: node %d not reachable from node %d\n", t, s);
				break;
			}

			if (iFlag == 1) { // one of the print formats
				printf("LENGTH: %d\n", myGraph->H[t].d);
			}

			else { // iFlag == 0 // the other print format
				pathPrinter(myGraph, t); // printing the path from the source to t
				printf("\n");
			}
			break;
		}

		default: break;
		}
	}
	return 0;
}