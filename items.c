#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//data structure for node
struct node{
    char name[20];
    struct node * next;
};

//data structure for list
struct list{
    struct node *head;
};

//initialize inventory
struct list *inventory;

//allocate memory to inventory
void setUpInventory(){
    //initialize inventory
    inventory = (struct list*) malloc(sizeof(struct list));
}

//return inventory
struct list* getInventory(){
    return inventory;
}

//add node to list
void add_item(struct list *items, char itemName[20]) {
    //create node and link to it
    struct node *link = (struct node*) malloc(sizeof(struct node));
    strcpy(link->name, itemName);
    link->next = NULL;
    //list is empty
    if(items->head == NULL){
        items->head = link;
        return;
    }

    struct node *curr = items->head;
    //iterate until last node
    while(curr->next != NULL){
        curr = curr->next;
    }

    //add to end
    curr->next = link;
}

//remove node from a list (also used to remove item from room)
int drop_item(struct list *items, char itemName[20]){
    //list is empty
    if(items->head == NULL){
        return -1;
    }
    //check head
    else if(strcmp(items->head->name, itemName) == 0){
        items->head = items->head->next;
        return 1;
    }
    struct node *curr = items->head;
    struct node *prev = NULL;
    //iterate to find node
    while(strcmp(curr->name, itemName)){
        //last node
        if(curr->next == NULL){
            return -1;
        }
        //get next node
        else{
            prev = curr;
            curr = curr->next;
        }
    }
    //found match
    prev->next = curr->next;
    return 1;
}