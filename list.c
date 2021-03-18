#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
  const void * data;
  Node * next;
  Node * prev;
};

struct List {
  Node * head;
  Node * tail;
  Node * current;
};

typedef List List;

Node * createNode(const void * data) {
  Node * new_node = (Node *)calloc(1, sizeof(Node));
  assert(new_node);
  if (!new_node) { return(NULL); }
  new_node->data = data;
  return(new_node);
}

List * createList() {
  List* new_list = calloc(1, sizeof(List));
  assert(new_list);
  if (!new_list) { return(NULL); }
  return(new_list);
}

void * firstList(List * list) {
  list->current = list->head;
  return(list->current);
}

void * nextList(List * list) {
  list->current = list->current->next;
  return(list->current);
}

void * lastList(List * list) {
  list->current = list->tail;
  return(list->current);
}

void * prevList(List * list) {
  list->current = list->current->prev;
  return(list->current);
}

void pushFront(List * list, const void * data) {
  Node* new_node = createNode(data);
  if (list->head)
  {
    list->head->prev = new_node;
    new_node->next = list->head;
  }
  else
  {
    // There is no head, so the list is empty.
    list->head = new_node;
    list->current = new_node;
  }
  list->head = new_node;
}

void pushBack(List * list, const void * data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List * list, const void * data) {
  if (list->current)
  {
    Node* new_node = createNode(data);
    Node* temp = list->current->next;
    list->current->next = new_node;
    new_node->next = temp;
    if (temp) { temp->prev = new_node; }
  }
  else
  {
    // Empty?
    pushFront(list, data);
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node* temp = list->current;
  Node* prev = temp->prev;
  Node* next = temp->next;

  if (prev) { prev->next = next; }
  if (next) { next->prev = prev; }

  const void* temp_data = temp->data;
  free(temp);
  return((void*)temp_data); // Fix the declaration! const void*
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}