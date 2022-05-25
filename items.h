#ifndef ITEMS_H_
#define ITEMS_H_

void add_item();
int drop_item();
void setUpInventory();
struct list* getInventory();
struct node{
    char name[20];
    struct node * next;
};
struct list{
    struct node * head;
};

#endif