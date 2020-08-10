// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#include "heap.h"

#include <stdio.h> 
// included for output in printHeap, Insert, DeleteMax, and IncreaseKey

#include <limits.h> 
// included to set the key of a new element to the lowest possible int value in the Insert function

#include <cmath> 
// included for use in the Insert function to calculate the 
// next largest power of 2 to use as the heap capacity


// takes in an index and returns the index of the parent - ensures not zero
int Parent(int i) {
	i = i / 2;
	if (i > 0) // if is larger than zero it is fine, if is not we need to return 1
		return i;
	else
		return 1;
}

// takes in an index and returns where the left child should be - no checking
int Left(int i) {
	return (2 * i);
}

// takes in an index and returns where the right child should be - no checking 
int Right(int i) {
	return (2 * i + 1);
}

// moves the value at index i down the tree until it is smaller than both of it's children
void MinHeapify(GRAPH* myGraph, int i) {
	int smallest = i; // smallest will be the compairison value
	int L = Left(i); // calculating the location of the children to make it easy
	int R = Right(i); 
	if ((L <= myGraph->v) && (myGraph->H[L].d < myGraph->H[smallest].d)) { 
		// finding out which value is the smallest as long as it is within the bounds of the sort array
		smallest = L; // saving the smaller value
	}
	if ((R <= myGraph->v) && (myGraph->H[R].d < myGraph->H[smallest].d)) { // same as above, just the other side
		smallest = R; 
	}
	if (smallest != i) { // if i is still the smallest, then we don't do anything, 
		// otherwise swap and call heapify again on the value that got lowered to move it down further
		ELEMENT key = myGraph->H[smallest]; // swapping
		myGraph->H[smallest] = myGraph->H[i];
		myGraph->H[i] = key;
		MinHeapify(myGraph, smallest); // the smallest variable now points to the index with the larger variable, so that is the one to move
	}
}

// loops through Element array A and writes the values of the keys into the Heap heap. 
void BuildHeap(GRAPH* myGraph) {
	for (int i = myGraph->v / 2; i > 0; i--) { // only sorting the elements that are in the front half of the amount that needs to be sorted
		MinHeapify(myGraph, i); // calling MinHeapify on the elements to move them into place
	}
}

// deletes the min element of the heap, and then reorders the heap appropriately
ELEMENT ExtractMin(GRAPH* myGraph) {
	ELEMENT min = myGraph->H[1]; // copying the min element into min
	myGraph->H[1] = myGraph->H[myGraph->v]; // writing over the min element with the last element in the heap
	myGraph->H[myGraph->v] = min;
	myGraph->v--; // "reducing" the array to prevent improper access 
	// - very important as the minHeap is called and we don't want the elements just "removed"
	// above to float back up to the top
	MinHeapify(myGraph, 1); // moving the largest element that was moved to the top down into it's new position 
	// somewhere where it obeys the laws of heap

	return min; // returning the element that holds the min
}

// looping through the .H array to find the index of where it is located
int findElement(GRAPH* myGraph, int key) {
	for (int i = 1; i <= myGraph->v; i++) { // looping through the array
		if (myGraph->H[i].node == key) { // if the .node/ name is the same as the key we are looking for 
			return i; // we return the index
		}
	}
	return 0; // if we can't find the location, it is not in the array
}

// reorganizes the .H array so that the index is the same as the .node for easier access
void reorder(GRAPH* myGraph) {
	ELEMENT temp; // variable for the swap
	int k;
	for (int i = 1; i < myGraph->v; i++) { // looping through the array 
		k = findElement(myGraph, i); // finding the location of the node that should be in i
		temp = myGraph->H[i]; // swapping into place
		myGraph->H[i] = myGraph->H[k];
		myGraph->H[k] = temp;
	}
}