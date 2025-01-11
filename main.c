#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"
#include "userbase.h"
#include "graph_str.h" 

#define SIZE 10

void reccomendation(user_node* hasht_user,int size) {
    for (int i = 0; i< size ; i++) {
        ll_node* ref = malloc(sizeof(ll_node));
        ref -> prod_id = 0;
        ref -> quantity = 0;
        ll_node* temp = hasht_user[i].head;
        if (temp == NULL) {
            printf("No suggestion for userId : %d\n",hasht_user->user_id);
        } else {
            while (temp != NULL) {
                if (temp -> quantity > ref -> quantity) {
                ref -> prod_id = temp -> prod_id;
                ref -> quantity = temp -> quantity;
                } 
                temp = temp -> next;
            }
            printf("We recommend product %d for user %s\n",ref -> prod_id,hasht_user[i].user_name);
        }        
    }
}


int main() {
    int num_users, num_products, main_choice, internal_choice;
    int search_key;
    NODE** view_graph = NULL; // Graph for viewing relationships
    NODE** purchase_graph = NULL; // Graph for purchase relationships

    // Track the currently active user
    int active_user_id = -1; 

    // Track bought products for the active user
    int bought_products[SIZE];
    int bought_count = 0;

    printf("Enter the maximum No. of users and products you will be entering separated by a space >> ");
    scanf("%d %d", &num_users, &num_products);

    // Initializing the hash tables
    user_node* hasht_user = malloc(num_users * sizeof(user_node)); 
    for (int i = 0; i < num_users; i++) {
        hasht_user[i].user_id = 0; 
        hasht_user[i].head = NULL;
        hasht_user[i].flag = 0;
        const char* name = "empty";
        strcpy(hasht_user[i].user_name, name); 
    }
  
    hashmap* hasht_prod = malloc(num_products * sizeof(hashmap)); 
    for (int i = 0; i < num_products; i++) {
        hasht_prod[i].count = 0; 
        hasht_prod[i].head = NULL; 
    }

    // Initialize graphs
    view_graph = malloc((num_products + 1) * sizeof(NODE*));
    purchase_graph = malloc((num_products + 1) * sizeof(NODE*));
    initgraph(view_graph, num_products);
    initgraph(purchase_graph, num_products);

    int* visited = malloc((num_products + 1) * sizeof(int)); // Visited array for graph traversal

    do {
        printf("Main Menu: 1. User Management 2. Product Management 3. View/Buy 4. Track Purchase History 5. Recommend products 6. QUIT\n");
        printf(">>> ");
        scanf("%d", &main_choice);

        switch (main_choice) {
            case 1: // User Management
                printf("User Management!\n");
                printf("1. Add User 2. Retrieve User 3. Update User\n");
                printf("-> ");
                scanf("%d", &internal_choice);
                switch (internal_choice) {
                    case 1:
                        // Add new user and set them as active
                        new_user(hasht_user, num_users);
                        printf("Enter the user ID of the newly added user to set as active: ");
                        scanf("%d", &active_user_id);
                        break;
                    case 2:
                        printf("Enter ID of user to be searched: ");
                        scanf("%d", &search_key);
                        search_user(search_key, hasht_user, num_users);
                        break;
                    case 3:
                        printf("Enter ID of user to be updated: ");
                        scanf("%d", &search_key);
                        edit_user(search_key, hasht_user, num_users);
                        break;
                    default:
                        printf("Invalid option!\n");
                        break;
                }
                break;

            case 2: // Product Management
                printf("Product Management!\n");
                printf("1. Add Product 2. Retrieve Product 3. Update Product\n");
                printf("-> ");
                scanf("%d", &internal_choice);
                switch (internal_choice) {
                    case 1:
                        insert_prod(hasht_prod, num_products);
                        break;
                    case 2:
                        printf("Enter ID of product to be searched: ");
                        scanf("%d", &search_key);
                        find_prod(hasht_prod, num_products, search_key);
                        break;
                    case 3:
                        printf("Enter ID of product to be updated: ");
                        scanf("%d", &search_key);
                        update_prod(hasht_prod, num_products, search_key);
                        break;
                    default:
                        printf("Invalid option!\n");
                        break;
                }
                break;

            case 3: // View/Buy
                printf("View/Buy\n");
                if (active_user_id == -1) {
                    printf("No active user selected. Please add a user first.\n");
                    break;
                }

                printf("1. View Products 2. Buy Products\n");
                printf("-> ");
                scanf("%d", &internal_choice);
                switch (internal_choice) {
                    case 1: { // View products and update view graph
                        display(hasht_prod, num_products);
                        int product1, product2;
                        printf("Enter product ID to view (or 0 to stop): ");
                        scanf("%d", &product1);

                        while (product1 != 0) {
                            printf("Enter ID of another product viewed after it (or 0 to stop): ");
                            scanf("%d", &product2);
                            if (product2 != 0) {
                                insertnode(view_graph, product1, product2);
                                printf("Added view relationship: %d -> %d\n", product1, product2);
                            }
                            product1 = product2;
                        }
                        break;
                    }
                    case 2: { // Buy products and update purchase graph
                        int user_id = active_user_id;
                        int product1, product2;
                        printf("Active User ID: %d\n", user_id);
                        printf("Enter product ID to buy (or 0 to stop): ");
                        scanf("%d", &product1);
                        incrementBuy(hasht_user,num_users,active_user_id, product1);
                        while (product1 != 0) {
                            // Add product to bought products list
                            bought_products[bought_count++] = product1;
                            printf("Added product %d to bought list.\n", product1);
                            printf("Enter ID of another product bought after it (or 0 to stop): ");
                            scanf("%d", &product2);
                            if (product2 != 0) {
                                incrementBuy(hasht_user,num_users,active_user_id, product2);
                                insertnode(purchase_graph, product1, product2);
                                printf("Added purchase relationship: %d -> %d\n", product1, product2);
                            }
                            product1 = product2;
                        }
                        break;
                    }
                    default:
                        printf("Invalid option!\n");
                        break;
                }
                break;

            case 4: // Track Purchase History
                printf("Track Purchase History\n");
                printf("1. View Graph 2. Purchase Graph\n");
                printf("-> ");
                scanf("%d", &internal_choice);
                switch (internal_choice) {
                    case 1: // BFS for view graph
                        printf("Enter product ID to start traversal: ");
                        scanf("%d", &search_key);
                        initvisited(visited, num_products);
                        printf("View Graph Traversal: ");
                        BFS(view_graph, search_key, num_products, visited);
                        printf("\n");
                        break;
                    case 2: // Check if at least one product is bought
                        if (bought_count == 1) {
                            printf("Purchased product ID: %d\n", bought_products[0]);
                        } else if (bought_count > 1) {
                            printf("Enter product ID to start traversal: ");
                            scanf("%d", &search_key);

                            // Check if the product is in the bought list
                            int valid_product = 0;
                            for (int i = 0; i < bought_count; i++) {
                                if (bought_products[i] == search_key) {
                                    valid_product = 1;
                                    break;
                                }
                            }

                            if (valid_product) {
                                initvisited(visited, num_products);
                                printf("Purchase Graph Traversal: ");
                                BFS(purchase_graph, search_key, num_products, visited);
                                printf("\n");
                            } else {
                                printf("Invalid product ID! Please enter a product from the bought list.\n");
                            }
                        } else {
                            printf("No products bought yet.\n");
                        }
                        break;
                    default:
                        printf("Invalid option!\n");
                        break;
                }
                break;

            case 5:
                printf("Printing the recoomende prodcut to buy for each user!\n");
                reccomendation(hasht_user,num_users);
                break;

            case 6:
              exit(1);
              break;

            default:
                printf("Invalid option!\n");
                break;
        }
    } while (main_choice != 6);

    // Cleanup
    free(view_graph);
    free(purchase_graph);
    free(hasht_user);
    free(hasht_prod);
    free(visited);

    return 0;
}
