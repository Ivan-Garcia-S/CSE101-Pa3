#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph A = newGraph(5);
   Graph B = newGraph(7);

   printf("order: %d\n", getOrder(A));
   printf("distance from source: %d\n", getDist(A,3));
   addEdge(A,1,3);
   printf("before second add\n");
   addEdge(A,1,5);
   printf("before third add\n");
   addEdge(A,2,5);
   addEdge(A,2,4);
   addEdge(A,3,4);
   addEdge(A,3,5);
   addEdge(A,4,5);
   printGraph(stdout,A);

   addEdge(B,1,3);
   addEdge(B,1,6);
   addEdge(B,1,7);
   addEdge(B,2,3);
   addEdge(B,2,7);
   addEdge(B,3,6);
   printGraph(stdout,B);
   //makeNull(B);
   printGraph(stdout,B);

   freeGraph(&A);
   freeGraph(&B);

   return (0);
}
