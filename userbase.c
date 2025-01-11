#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int flag; //1 if occupied else zero
} user_node;

// Insert using Linear Probing
void insertUser(int uid, user_node *hashTable, int size, char* name) {
    int hash, i = 0;
    hash = ((uid % size) + i) % size;
    while (hashTable[hash].flag != 0 && i < size) {
        i++;                              // Increment number of collisions
        hash = ((uid % size) + i) % size; // New hash value
    }
    if (hashTable[hash].flag == 0) {
        hashTable[hash].user_id = uid;
        hashTable[hash].flag = 1;
        strcpy(hashTable[hash].user_name, name);
        printf("The data %d is inserted at %d\n", uid, hash);
    }
    else {
        printf("\nData cannot be inserted\n");
    }
}

void search_user(int key, user_node* hasht_user,int size) {
    int hash, i = 0;
    hash = ((key % size) + i) % size;
    while (i < size)
    {
        if (hasht_user[hash].user_id == key && hasht_user[hash].flag == 1) {
            printf("\nThe data %d-%s is found at location %d\n",key,hasht_user[hash].user_name, hash);
            return;
        }
        i++;
        hash = ((key % size) + i) % size;
    }
    printf("\nData not found\n");
}

user_node* mainfunc(int size) {
    user_node* hasht_user = malloc(size * sizeof(user_node)); 
    for (int i = 0; i < size; i++) {
      hasht_user[i].user_id = 0; 
      hasht_user[i].head = NULL;
      hasht_user[i].flag = 0;
      const char* name = "empty";
      strcpy(hasht_user[i].user_name,name); 
    }
    for (int i = 0; i< size; i++) {
        printf("Enter user id for %d : ",i);
        int n;
        scanf("%d",&n);
        printf("Enter user name for %d", i);
        char name[100];
        scanf(" %[^\n]",name);
        insertUser(n,hasht_user,size,name);
    }
    return hasht_user;
}

void new_user(user_node* hasht_user,int size) {
    printf("Enter user id : ");
    int n;
    scanf("%d",&n);
    printf("Enter user name : ");
    char name[100];
    scanf(" %[^\n]",name);
    insertUser(n,hasht_user,size,name);
}

void edit_user(int key, user_node* hasht_user,int size) {
    int hash, i = 0;
    hash = ((key % size) + i) % size;
    while (i < size)
    {
        if (hasht_user[hash].user_id == key && hasht_user[hash].flag == 1) {
            char new_name[100];
            printf("Enter the new name you want to edit : ");
            scanf("%s",new_name);
            strcpy(hasht_user[hash].user_name,new_name);
            printf("user name updated!\n");
            return;
        }
        i++;
        hash = ((key % size) + i) % size;
    }
    printf("\nData not found\n");
}

void incrementBuy(user_node* hasht_user,int size, int uid, int pid) {
    int hash, i = 0;
    hash = ((uid % size) + i) % size;
    while (i < size)
    {
        if (hasht_user[hash].user_id == uid && hasht_user[hash].flag == 1) {
            if (hasht_user[hash].head == NULL) {
                ll_node* new_node = malloc(sizeof(ll_node));
                new_node -> prod_id = pid;
                new_node -> quantity = 1;
                new_node -> next = NULL;
                hasht_user[hash].head = new_node;
            } else {
                ll_node* temp = hasht_user[hash].head;
                while(temp != NULL && temp -> prod_id != pid) {
                    temp = temp -> next;
                }
                if (temp != NULL && temp -> prod_id == pid ) {
                    (temp -> quantity)++;
                } else {
                    ll_node* new_node = malloc(sizeof(ll_node));
                    new_node -> prod_id = pid;
                    new_node -> quantity = 1;
                    new_node -> next = hasht_user[hash].head;
                    hasht_user[hash].head = new_node;
                }
            }
            return;
        }
        i++;
        hash = ((uid % size) + i) % size;
    }
    printf("\nData not found\n");
}