// Developer: John Cody
// Date: 04/26/2020
// Class: CSE 310 @ ASU
// Taught by: Guoliang Xue
// Project Name: P02

#pragma once // done so that this file is only ever included once in other files

#include "structs.h"
#include "graph.h"

int Parent(int i);
// takes in an index and returns the index of the parent - no checking

int Left(int i);
// takes in an index and returns where the left child should be - no checking

int Right(int i);
// takes in an index and returns where the right child should be - no checking

void MinHeapify(GRAPH* myGraph, int i);
// moves the value at index i down the tree until it is not larger than both of it's children

void BuildHeap(GRAPH* myGraph);
// creates a min heap in the ELEMENT array in myGraph

ELEMENT ExtractMin(GRAPH* myGraph);
// deletes the max element of the heap, and then reorders the heap appropriately

int findElement(GRAPH* myGraph, int key);
// finds an ELEMENT in the array and returns its address

void reorder(GRAPH* myGraph); 
// organizes the nodes so that the .node is the same as the index for easier access