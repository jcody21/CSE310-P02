Developer: John Cody
Date: 04/26/2020
Class: CSE 310 @ ASU
Taught by: Guoliang Xue
Project Name: P02

The goal of this project it to implement Dijkstra's shortest path algorithm in order to find the shortest distance or route between elements in a weighted directed graph. 

This project uses the C++ coding language, and was originally developed using the g++ compiler, but can be easily run in Visual Studio by uncommenting the line in the top of the util.cpp file that starts with "#pragma".

This is done with the use of three specialty structs that store information about each element/node/vertex (ELEMENT), about each edge in the from of a list (LIST), and about the graph as a whole (GRAPH). 


CONTROLS:
"S": stops the program and deletes all dynamically allocated data before exiting. 

"R": reads in the number of verticies, the number of edges, and information about each edge from a file. The file to access is set to "Ginput.txt" by default, but that can be easily changed by altering the INPUT_FILE character array at the top of the main function. To create your own input file see the section "Creating Your Own Graph File" below. 

"W": writes the number of verticies, the number of edges, and the edge adjacency list where it follows the format "start: (end, weight)".

"F start end flag": finds the shortest distance/route from the start element to the ending element. The flag (0 or 1) determines whether to output the length of the path(1), or the route taken(0). 


Creating Your Own Graph File: 
The file to be accessed just needs to have the format: 
"verticies edges
startingVertex endingVertex weight" 
where verticies is the number of verticies, edges is the number of edges, startingVertex is the vertex where the edge starts, endingVertex is where the edge ends, and weight is the weight of the edge. For each edge just setup like above, but put each edge on a new line. To create a graph that is undirected, just double the number of edges and give every edge an inverse where it goes in the opposite direction, but has the same weight. 