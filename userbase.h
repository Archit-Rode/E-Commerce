#ifndef USER_HASH_TABLE_H
#define USER_HASH_TABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define SIZE 10 

typedef struct ll_node {
    int prod_id;               
    int quantity;              
    struct ll_node* next;      
} ll_node;

typedef struct user_node {
    int user_id;              
    char user_name[100];       
    struct ll_node* head;      
    int flag;                  
} user_node;

void insertUser(int uid, user_node *hashTable, int size, char* name);
user_node* mainfunc(int size);
void new_user(user_node* hasht_user,int size);
void search_user(int key, user_node* hasht_user,int size);
void edit_user(int key, user_node* hasht_user,int size);
void incrementBuy(user_node* hasht_user,int size, int uid, int pid);

#endif
