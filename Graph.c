/*********************************************************************************
 * * Ivan Garcia-Sanchez, igarci33
 * * 2020 Spring CSE101 PA2
 * * List.c
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>
//#include "List.c"
//#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
   List* neighbors;
   char* color;
   int* parent;
   int* distance;
   int vertices;
   int edges;
   int source;
} GraphObj;

typedef GraphObj* Graph;

Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->neighbors = calloc(n+1,sizeof(List));
   G->color = calloc(n+1,sizeof(char));
   G->parent = calloc(n+1,sizeof(int));
   G->distance = calloc(n+1,sizeof(int));
   G->vertices = n;
   G->edges = 0;
   G->source = NIL;

   for(int i = 1; i <= n; i++){
      G->neighbors[i] = newList();
   }
   for(int i = 1; i <= n; i++){
      G->color[i] = 'w';
   }
   for(int i = 1; i <= n; i++){
      G->parent[i] = NIL;
   }
   for(int i = 1; i <= n; i++){
      G->distance[i] = INF;
   }
   return G;
}

void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL){
      for(int i = 1; i <= (*pG)->vertices; i++){
         freeList(&(*pG)->neighbors[i]);	
      }
      free((*pG)->neighbors);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->distance);
      (*pG)->neighbors = NULL;
      (*pG)->color = NULL;
      (*pG)->distance = NULL;
      (*pG)->parent = NULL;
      free(*pG);
      *pG = NULL;
   }
}

int getOrder(Graph G){
   return G->vertices;
}

int getSize(Graph G){
   return G->edges;
}

int getSource(Graph G){
   return G->source;
}

int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() on out of bounds vertex\n");
      exit(1);
   }
   if(getSource(G) == NIL){
      return NIL;	
   }
   if(!isEmpty(G->neighbors[getSource(G)])) printList(stdout,G->neighbors[getSource(G)]);
   return G->parent[u];
}

int getDist(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDist() on out of bounds vertex\n");
      exit(1);
   }
   if(getSource(G) == NIL){
      return INF;
   }
   return G->distance[u];
}

void getPath(List L, Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getPath() on out of bounds vertex\n");
      exit(1);
   }
   if(getSource(G) == NIL){
      printf("Graph Error: calling getPath() with no source vertex\n");
      exit(1);
   }
   if(u == getSource(G)){
      append(L,getSource(G));
   }
   else if(getParent(G,u) == NIL){
      append(L,NIL);
   }
   else{
      getPath(L,G,getParent(G,u));
      append(L,u);
   }
}

void makeNull(Graph G){
   G->edges = 0;
   G->source = NIL;
   for(int i = 1; i <= getOrder(G); i++){
      clear(G->neighbors[i]);
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->color[i] = 'w';
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->parent[i] = NIL;
   }
   for(int i = 1; i <= getOrder(G); i++){
      G->distance[i] = INF;
   }

}

void addEdge(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() on out of bounds vertex\n");
      exit(1);
   }
   G->edges++;
   
   //Adds v to U adjacency list
   if(length(G->neighbors[u]) == 0){
      append(G->neighbors[u],v);
   }
   else{
      moveFront(G->neighbors[u]);
      bool appU = false;
      while(index(G->neighbors[u]) != -1 && !appU){
         if(v < get(G->neighbors[u])){
            insertBefore(G->neighbors[u],v);
            appU = true;
         }
         else{
            moveNext(G->neighbors[u]);
         }
      }
      if(!appU){
         append(G->neighbors[u],v);
      }
   }
   //Adds u to V adjacency list
   if(length(G->neighbors[v]) == 0){
      append(G->neighbors[v],u);
   }
   else{
      moveFront(G->neighbors[v]);
      bool appV = false;
      while(index(G->neighbors[v]) != -1 && !appV){
         if(u < get(G->neighbors[v])){
            insertBefore(G->neighbors[v],u);
            appV = true;
         }
         else{
            moveNext(G->neighbors[v]);
         }
      }
      if(!appV){
         append(G->neighbors[v],u);
      }
   }
}

void addArc(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() on out of bounds vertex\n");
      exit(1);
   }
   G->edges++;
   
   //Adds v to U adjacency list
   if(length(G->neighbors[u]) == 0){
      append(G->neighbors[u],v);
   }
   else{
      moveFront(G->neighbors[u]);
      bool appU = false;
      while(index(G->neighbors[u]) != -1 && !appU){
         if(v < get(G->neighbors[u])){
            insertBefore(G->neighbors[u],v);
            appU = true;
         }
         else{
            moveNext(G->neighbors[u]);
         }
      }
      if(!appU){
         append(G->neighbors[u],v);
      }
   }
}

void BFS(Graph G, int s){
   G->source = s;
   for(int i = 1; i <= getOrder(G); i++){
         G->color[i] = 'w';
         G->distance[i] = INF;
         G->parent[i] = NIL;
   }
   List queue = newList();
   G->color[s] = 'g';
   G->distance[s] = 0;
   G->parent[s] = NIL;
   prepend(queue,s);
  
   while(!isEmpty(queue)){
      int u = front(queue);
      deleteFront(queue);
      if(!isEmpty(G->neighbors[u])){
         moveFront(G->neighbors[u]);
         while(index(G->neighbors[u]) != -1){
            int v = get(G->neighbors[u]); 
            if(G->color[v] == 'w'){
               G->color[v] = 'g';
               G->distance[v] = G->distance[u] + 1;
               G->parent[v] = u;
               append(queue,v);
            }
           // G->color[u] = 'b';
            moveNext(G->neighbors[u]);
         }
      }
      G->color[u] = 'b';
   }
   freeList(&queue);
}

void printGraph(FILE* out, Graph G){
   for(int i = 1; i <= getOrder(G); i++){
      fprintf(out,"%d:",i);
      if(length(G->neighbors[i]) != 0){
         fprintf(out," ");
         moveFront(G->neighbors[i]);
         while(index(G->neighbors[i]) != -1){
            fprintf(out,"%d",get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
            if(index(G->neighbors[i]) != -1){
               fprintf(out," ");
            }
            else{
               if(i != getOrder(G)) fprintf(out,"\n");
            }	
         }
      }
      else{
         fprintf(out,"\n");
      }
   }
   fprintf(out,"\n");
}
