/*********************************************************************************
 * * Ivan Garcia-Sanchez, igarci33
 * * 2020 Spring CSE101 PA3
 * * Graph.h
 * * *********************************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"
#define INF -2
#define NIL -1

typedef struct GraphObj* Graph;


// Creates and returns a new empty Graph
Graph newGraph(int n);

// Frees all heap memory associated with *pG
void freeGraph(Graph* pG);

//Returns order of the graph
int getOrder(Graph G);

//Returns size of the graph
int getSize(Graph G);

//Returns the source vertex most recently used in function BFS()
int getSource(Graph G);

// Returns the parent of vertex u in the BreadthFirst tree created by BFS(),
//or NIL if BFS() has not yet been called.
//Pre: 1 <= u <= getOrder(G) 
int getParent(Graph G, int u);

//Returns the distance from the most recent BFS source to vertex u, 
//or INF if BFS() has not yet been called. 
//Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u);

// Appends to the List L the vertices of a shortest path in G from source to u, 
//or appends to L the value NIL if no such path exists. 
//Pre:  getSource(G) != NIL, 1 <= u <= getOrder(G) 
void getPath(List L, Graph G, int u);

// Deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G);

// Inserts a new edge joining u to v, i.e.  i.e. u is added to the adjacency 
//List of v, and v to the adjacency List of u.
//Pre: 1 <=  u,v <= getOrder(G)
void addEdge(Graph G, int u, int v);

//Inserts a new directed edge from u to v, i.e. v is added to the adjacency 
//List of u (but not u to the adjacency List of v)
//Pre: 1 <=  u,v <= getOrder(G)
void addArc(Graph G, int u, int v);

//Runs the BFS algorithm on the Graph G with source s, setting the color, 
//distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

//Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
