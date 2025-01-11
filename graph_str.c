#include <stdio.h>
#include <stdlib.h>
#include "graph_str.h"

// Initialize a queue
void initQueue(QUEUE_NODE* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmpty(QUEUE_NODE* q) {
    return q->front == -1;
}

// Add an item to the queue
void enqueue(QUEUE_NODE* q, int data) {
    if (q->rear == MAXNODES - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->data_arr[++q->rear] = data;
}

// Remove an item from the queue
int dequeue(QUEUE_NODE* q) {
    if (isEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->data_arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return data;
}

// Initialize the adjacency list for the graph
void initgraph(NODE** listnodes, int n) {
    for (int i = 1; i <= n; i++) {
        listnodes[i] = NULL;
    }
}

// Insert a new edge between vertices i and j
void insertnode(NODE** listnodes, int i, int j) {
    NODE* adj_to_i = (NODE*)malloc(sizeof(NODE));
    adj_to_i->index = j;
    adj_to_i->next = NULL;

    NODE* temp = NULL;
    if (listnodes[i] == NULL) {
        listnodes[i] = adj_to_i;
    } else {
        temp = listnodes[i];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = adj_to_i;
    }
}

// Display the adjacency list
void displaygraph(NODE** listnodes, int n) {
    for (int i = 1; i <= n; i++) {
        NODE* current = listnodes[i];
        printf("Adjacent vertices to vertex %d: ", i);
        while (current != NULL) {
            printf("%d ", current->index);
            current = current->next;
        }
        printf("\n");
    }
}

// Initialize the visited array
void initvisited(int* visited, int n) {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
}

// Depth First Search (DFS)
void DFS(NODE** listnodes, int start, int n, int* visited) {
    visited[start] = 1;
    printf("%d ", start);

    NODE* temp = listnodes[start];
    while (temp != NULL) {
        if (!visited[temp->index]) {
            DFS(listnodes, temp->index, n, visited);
        }
        temp = temp->next;
    }
}

// Breadth First Search (BFS)
void BFS(NODE** listnodes, int start, int n, int* visited) {
    QUEUE_NODE queue;
    initQueue(&queue);

    enqueue(&queue, start);
    visited[start] = 1;

    while (!isEmpty(&queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        for (NODE* temp = listnodes[current]; temp != NULL; temp = temp->next) {
            if (!visited[temp->index]) {
                enqueue(&queue, temp->index);
                visited[temp->index] = 1;
            }
        }
    }
}