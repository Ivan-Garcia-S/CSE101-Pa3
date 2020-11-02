/*********************************************************************************
 * * Ivan Garcia-Sanchez, igarci33
 * * 2020 Spring CSE101 PA2
 * * List.c
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj{
   object data;
   char* value;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

Node newNode(object num){
   Node N = malloc(sizeof(NodeObj));
   N->data = num;
   N->next = NULL;
   N->prev = NULL;
   return N;
}

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int ind;
} ListObj;

typedef ListObj* List;

List newList(){
   List L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->cursor = NULL;
   L->back = L->front;
   L->length = 0;
   L->ind = -1;
   return L;
}

void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL){
      if(!isEmpty(*pL)) clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}

void freeNode(Node* pN){
   if(pN!=NULL && *pN!=NULL){
      free(*pN);
      *pN = NULL;
   }
}

bool isEmpty(List L) {
   if(L==NULL){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return length(L) == 0;
}


int length(List L) {
   if(L==NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
  return L->length;
}

int index(List L){
   if(L==NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->ind;
}

object get(List L){
   if(L==NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor==NULL){
      printf("Cursor Error: calling get() on NULL cursor\n");
      exit(1);
   }
  return L->cursor->data;
}

void set(List L, object x){
   if(L==NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor==NULL){
      printf("Cursor Error: calling get() on NULL cursor\n");
      exit(1);
   }
   L->cursor->data = x;
}

object front(List L){
   if(L==NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return L->front->data;
}
object back(List L){
   if(L==NULL){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return L->back->data;
}

int equals(List A, List B){
   int eq = 0;
   Node tempA = NULL;
   Node tempB = NULL;

   if(A==NULL || B==NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   eq = ( A->length == B->length );
   tempA = A->front;
   tempB = B->front;

   while(eq && tempA!=NULL){
      eq = (tempA->data == tempB->data);
      tempA = tempA->next;
      tempB = tempB->next;
   }
   return eq;
}

void moveFront(List L){
    if(L==NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling moveFront() on an empty List\n");
      exit(1);
   }
   L->cursor = L->front;
   L->ind = 0;
}

void moveBack(List L){
   if(L==NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling moveBack() on an empty List\n");
      exit(1);
   }
L->cursor = L->back;
   L->ind = L->length - 1;
}

void moveNext(List L){
   if(L==NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling moveNext() on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->back || L->cursor == NULL){
      L->cursor = NULL;
      L->ind = -1;
   }
   else{
      L->cursor = L->cursor->next;
      L->ind++;
   }
}


void movePrev(List L){
   if(L==NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling movePrev() on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->front || L->cursor == NULL){
      L->cursor = NULL;
      L->ind = -1;
   }
   else{
      L->cursor = L->cursor->prev;
      L->ind--;
   }
}

void prepend(List L, object data){
   Node insert = newNode(data);
   if(L->front == NULL) {
      L->front = insert;
      L->back = L->front;
   }
   else{
      insert->next = L->front;
      L->front->prev = insert;
      L->front = insert;
   }
   L->length++;
 if(L->ind >= 0){
      L->ind++;
   }
}

void append(List L, object data){
   Node insert = newNode(data);
   if(L->front == NULL) {
      L->front = insert;
      L->back = L->front;
   }
   else{
      insert->prev = L->back;
      L->back->next= insert;
      L->back = insert;
   }
   L->length++;
}

void insertBefore(List L, object data){
   if(L==NULL){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(1);
   }
   if(L->ind < 0){
      printf("Cursor Error: calling insertBefore() with NULL cursor\n");
      exit(1);
   }
   if(L->ind == 0){
      prepend(L,data);
   }
   else{
      Node insert = newNode(data);
      insert->next = L->cursor;
      L->cursor->prev->next = insert;
      insert->prev = L->cursor->prev;
      L->cursor->prev = insert;
      L->length++;
      L->ind++;
   }
}

void insertAfter(List L, object data){
   if(L==NULL){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
printf("List Error: calling insertAfter() on an empty List\n");
      exit(1);
   }
   if(L->ind < 0){
      printf("Cursor Error: calling insertAfter() with NULL cursor\n");
      exit(1);
   }
   if(L->ind == L->length-1){
      append(L,data);
   }
   else{
      Node insert = newNode(data);
      insert->prev = L->cursor;
      L->cursor->next->prev = insert;
      insert->next = L->cursor->next;
      L->cursor->next = insert;
      L->length++;
   }
}

void deleteFront(List L){
   if(L==NULL){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   Node free = L->front;
   if(L->ind <= 0){
      L->ind = -1;
      L->cursor = NULL;
   }
   else{
      L->ind--;
   }
   if(length(L)>1 ) {
      L->front = L->front->next;
   }
   else{
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&free);
}

void deleteBack(List L){
   if(L==NULL){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
 }
   if(isEmpty(L)){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   Node free = L->back;
   if(L->ind == L->length - 1){
      L->ind = -1;
      L->cursor = NULL;
   }
   if(length(L)>1 ) {
      L->back->prev->next = NULL;
      L->back = L->back->prev;
   }
   else{
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&free);
}

void delete(List L){
   if(L==NULL){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(L)){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if(L->ind < 0){
      printf("Cursor Error: calling delete() with NULL cursor\n");
      exit(1);
   }

   if(L->ind == L->length - 1){
      deleteBack(L);
   }
   else if(L->ind == 0){
      deleteFront(L);
   }
   else{
      L->ind = -1;
      Node free = L->cursor;

      if(length(L)>1 ) {
         L->cursor->prev->next = L->cursor->next;
         L->cursor->next->prev = L->cursor->prev;
      }
      L->cursor = NULL;
      L->length--;
      freeNode(&free);
   }
}
void clear(List L) {
   if(L==NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while(!isEmpty(L)){
      deleteFront(L);
   }
}

void printList(FILE* out, List L){
   Node place = L->cursor;
   int indx = L->ind;
   moveFront(L);
   while(L->ind >= 0){
       int print = get(L);
       fprintf(out, "%d ",print);
      moveNext(L);
   }
   L->cursor = place;
   L->ind = indx;
}

List copyList(List L){
   List copy = newList();
   if(length(L) != 0){
      Node place = L->cursor;
      int indx = L->ind;
      moveFront(L);
      while(L->ind >= 0){
         int num = get(L);
         append(copy,num);
         moveNext(L);
      }
      L->cursor = place;
      L->ind = indx;
   }
   return copy;
}
