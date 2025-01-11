This folder contains the 2024 DSA Jackfruit Problem submission by Team 7 from Section B CSE branch of PESU ECC. 

Instructions to run the code :   
On mac : 
```sh
clang main.c prod.c userbase.c graph_str.c -o main
```
On windows : 
```sh
gcc main.c prod.c userbase.c graph_str.c -o main
```
## Data Structures used in the Code : 
The entire project was constructed mainly using two data structures ; hash tables and graphs. 
There are two types of Hash tables used in this project. For storing the users we stored all user data in a hash table using linear probing, so that each field in the array is utilized, allowing us to store individual’s purchases using nodes of linked list. Whereas for the product item storage, we preferred a hash table with separate chaining, as it did not require any separate data holding for users as such 

Once all these purchase and user details were stored, while viewing and purchasing, each instance was updated using graphs. This is done so because once all purchases, and browsing is over, we can create a graph of which products were viewed and which not  for each individual user on demand. Graphs are the better choice for such a task.

Finally the recommendation is done based on the most bought item for each person. So if a person has bought product "A" a lot of times, he will be recommended that product. In the future it is possible to predict the top 3 or 5 products. 