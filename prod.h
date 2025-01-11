#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct node1 {
    int id;
    char prod_name[100];
    int prod_count;
    struct node1* next;
} node;

typedef struct {
    int count;
    struct user_node* head;
} hashmap;

node* createNode(int key, char* name);
void insertNode(int key, int size, char* name, hashmap* hashtable);
void display(hashmap* hashtable, int size);
hashmap* HashTable(int size);
void display(hashmap* hashtable, int size);
void insert_prod(hashmap* hasht_prod,int size);
void find_prod(hashmap* hasht_prod,int size, int pid);
void update_prod(hashmap* hasht_prod,int size, int pid);

#endif
