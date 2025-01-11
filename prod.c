#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct node1 {//represents a product
  int id;
  char prod_name[100];
  int prod_count;
  struct node1* next;
} node;

typedef struct  {//represents an entry into the hashtable
  int count; // The count is for each poistion in the hashmap to count how many nodes are present. 
  struct node1* head;
} hashmap;

node* createNode(int key, char* name) {
  node* new_node = malloc(sizeof(node));
  new_node -> id =  key;
  new_node -> next = NULL;
  new_node ->  prod_count = 0;
  strcpy(new_node -> prod_name, name);
  return new_node;
}

void insertNode(int key,int size, char* name,hashmap* hashtable ) {// inserts a product into the hashtable
  node* new_node = createNode(key,name);
  int hash = key%size;
  if (hashtable[hash].head == NULL) {
    hashtable[hash].head = new_node;
  } else {
    new_node -> next = hashtable[hash].head;
    hashtable[hash].head = new_node;
  }
  hashtable[hash].count++; 
}

void display(hashmap* hashtable, int size) {
    for (int i = 0; i < size; i++) {
        printf("Index %d -> ", i);
        node* temp = hashtable[i].head;
        while (temp != NULL) {
            printf("%d-%s ", temp->id, temp->prod_name);
            temp = temp->next;
        }
        printf("\n");
    }
}

void insert_prod(hashmap* hasht_prod,int size) {//inserts a product using user input
  int id;
  char prod_name[100];
  printf("Enter prod id >> ");
  scanf("%d",&id);
  printf("Enter product name >>");
  scanf(" %[^\n]",prod_name);
  insertNode(id, size, prod_name,hasht_prod);
  printf("Product inserted!\n");
}

void find_prod(hashmap* hasht_prod,int size, int pid) {
  int hash = pid%size;
  node* temp = hasht_prod[hash].head;
  while (temp != NULL) {
    if (temp -> id == pid) {
      printf("Found product %d-%s\n",pid,temp -> prod_name);
      return;
    }
    temp = temp -> next;
  }
  printf("Product not found!\n");
}

void update_prod(hashmap* hasht_prod,int size, int pid) {
  int hash = pid%size;
  node* temp = hasht_prod[hash].head;
  while (temp != NULL) {
    if (temp -> id == pid) {
      printf("Enter new product name : ");
      char name[100];
      scanf("%s",name);
      strcpy(hasht_prod[hash].head -> prod_name,name);
      printf("Updated product name!\n");
      return;
    }
    temp = temp -> next;
  }
  printf("Product not found!\n");
}