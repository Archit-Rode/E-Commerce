#ifndef GRAPH_STR_H
#define GRAPH_STR_H

#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 11

typedef struct node {
    int index;
    struct node* next;
} NODE;

typedef struct queue_node {
    int data_arr[MAXNODES];
    int front;
    int rear;
} QUEUE_NODE;

// Queue operations
void enqueue(QUEUE_NODE* q, int data);
int dequeue(QUEUE_NODE* q);
int isEmpty(QUEUE_NODE* q);

// Graph operations
void initgraph(NODE** listnodes, int n);
void insertnode(NODE** listnodes, int i, int j);
void displaygraph(NODE** listnodes, int n);
void initvisited(int* visited, int n);
void DFS(NODE** listnodes, int start, int n, int* visited);
void BFS(NODE** listnodes, int start, int n, int* visited);

#endif
