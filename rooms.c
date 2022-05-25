#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "items.h"

//struct for room
struct Room {
    char name[30];
    char character[50];
    struct list * itemList;
    struct Room * North;
    struct Room * South;
    struct Room * East;
    struct Room * West;
} topLeft, topMid, topRight, midLeft, midMid, midRight, botLeft, botMid, botRight;

//initialize current room
struct Room *currentRoom;

//initialize correct room, character, and item
struct Room correctRoom;
char correctCharacter[20];
char correctItem[15];

//array of characters
char characters[5][10] = {
    "cook", "mechanic", "wife", "husband", "grandpa"
};

//array of items;
char items[6][12] = {
    "knife", "wrench", "sword", "glass", "guitar", "gun"
};

//check input against correct character
bool guessChar(char guess[20]){
    if(strcmp(guess, correctCharacter) == 0){
        return true;
    }
    return false;
}

//check input against correct item
bool guessItem(){
    bool correct = false;
    //check inventory for item
    struct node *curr = getInventory()->head;
    while(curr != NULL){
        if(strcmp(curr->name, correctItem)){
            correct = true;
        }
        curr = curr->next;
    }
    //check room for item
    curr = currentRoom->itemList->head;
    while(curr != NULL){
        if(strcmp(curr->name, correctItem)){
            correct = true;
        }
        curr = curr->next;
    }
    return correct;
}

//check input against correct room
bool guessRoom(){
    if(strcmp(currentRoom->name, correctRoom.name) == 0){
        return true;
    }
    return false;
}

//check input against character array(for retyping character if wrong)
bool checkCharacterInput(char input[20]){
    bool exists = false;
    for(int i = 0; i < 5; i++){
        if(strcmp(characters[i], input) == 0){
            exists = true;
        }
    }
    return exists;
}

//search array for value
bool search(int arr[], int value){
    bool flag = false;
    for(int i = 0; i < 9; i++){
        if(arr[i] == value){
            flag = true;
        }
    }
    return flag;
};

//randomize room layout
void setUpRooms(){
    //create items
    struct node *knife = (struct node*) malloc(sizeof(struct node));
    strcpy(knife->name, "knife");
    knife->next = NULL;
    struct node *wrench = (struct node*) malloc(sizeof(struct node));
    strcpy(wrench->name, "wrench");
    wrench->next = NULL;
    struct node *sword = (struct node*) malloc(sizeof(struct node));
    strcpy(sword->name, "sword");
    sword->next = NULL;
    struct node *glass = (struct node*) malloc(sizeof(struct node));
    strcpy(glass->name, "glass");
    glass->next = NULL;
    struct node *guitar = (struct node*) malloc(sizeof(struct node));
    strcpy(guitar->name, "guitar");
    guitar->next = NULL;
    struct node *gun = (struct node*) malloc(sizeof(struct node));
    strcpy(gun->name, "gun");
    gun->next = NULL;

    //create lists
    struct list *kitchenItems = (struct list*) malloc(sizeof(struct list));
    kitchenItems->head = knife;
    struct list *bathroomItems = (struct list*) malloc(sizeof(struct list));
    bathroomItems->head = NULL;
    struct list *garageItems = (struct list*) malloc(sizeof(struct list));
    garageItems->head = wrench;
    struct list *pantryItems = (struct list*) malloc(sizeof(struct list));
    pantryItems->head = glass;
    struct list *masterBedroomItems = (struct list*) malloc(sizeof(struct list));
    masterBedroomItems->head = sword;
    struct list *guestBedroomItems = (struct list*) malloc(sizeof(struct list));
    guestBedroomItems->head = NULL;
    struct list *livingRoomItems = (struct list*) malloc(sizeof(struct list));
    livingRoomItems->head = guitar;
    struct list *diningRoomItems = (struct list*) malloc(sizeof(struct list));
    diningRoomItems->head = NULL;
    struct list *atticItems = (struct list*) malloc(sizeof(struct list));
    atticItems->head = gun;

    //array of rooms
    struct Room roomArray[9] = {
    {"kitchen", "cook", kitchenItems},
    {"bathroom", .itemList = bathroomItems},
    {"garage", "mechanic", garageItems},
    {"pantry", "wife", pantryItems},
    {"master bedroom", "husband", masterBedroomItems},
    {"guest bedroom", .itemList = guestBedroomItems},
    {"living room", .itemList = livingRoomItems},
    {"dining room", .itemList = diningRoomItems},
    {"attic", "grandpa", atticItems}
    };

    //initialize rand()
    srand(time(NULL));

    //generate random array of indices
    int randArray[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    for(int i = 0; i < 9; i++){
        bool done = false;
        while(!done){
            int x;
            x = rand() % 9;
            if(!search(randArray, x)){
            randArray[i] = x;
            done = true;
            }
        }
    };

    //randomly initialize rooms
    topLeft = roomArray[randArray[0]];
    topMid = roomArray[randArray[1]];
    topRight = roomArray[randArray[2]];
    midLeft = roomArray[randArray[3]];
    midMid = roomArray[randArray[4]];
    midRight = roomArray[randArray[5]];
    botLeft = roomArray[randArray[6]];
    botMid = roomArray[randArray[7]];
    botRight = roomArray[randArray[8]];

    //choose random correct trio
    correctRoom = roomArray[rand() % 9];
    strcpy(correctCharacter, characters[rand() % 5]);
    strcpy(correctItem, items[rand() % 6]);

    //setup room layout
    //top
    topLeft.East = &topMid;
    topLeft.South = &midLeft;

    topMid.West = &topLeft;
    topMid.South = &midMid;
    topMid.East = &topRight;

    topRight.West = &topMid;
    topRight.South = &midRight;

    //middle
    midLeft.North = &topLeft;
    midLeft.East = &midMid;
    midLeft.South = &botLeft;

    midMid.East = &midRight;
    midMid.North = &topMid;
    midMid.West = &midLeft;
    midMid.South = &botMid;

    midRight.North = &topRight;
    midRight.West = &midMid;
    midRight.South = &botRight;

    //bottom
    botLeft.North = &midLeft;
    botLeft.East = &botMid;

    botMid.West = &botLeft;
    botMid.North = &midMid;
    botMid.East = &botRight;

    botRight.North = &midRight;
    botRight.West = &botMid;

    //start in middle of house
    currentRoom = &midMid;
}

//return current location
struct Room* location(){
    return currentRoom;
}

//follow pointer to room in direction of input
void go(char direction[10]){
    if(strcmp(direction, "north") == 0){
        if(currentRoom->North!=NULL){
            currentRoom = currentRoom->North;
            printf("You are now in the %s.\n", currentRoom->name);
        }
        else{
            printf("You can't go north any further.\n");
        }
    }
    else if(strcmp(direction, "east") == 0){
        if(currentRoom->East!=NULL){
            currentRoom = currentRoom->East;
            printf("You are now in the %s.\n", currentRoom->name);
        }
        else{
            printf("You can't go east any further.\n");
        }
    }
    else if(strcmp(direction, "south") == 0){
        if(currentRoom->South!=NULL){
            currentRoom = currentRoom->South;
            printf("You are now in the %s.\n", currentRoom->name);
        }
        else{
            printf("You can't go south any further.\n");
        }
    }
    else if(strcmp(direction, "west") == 0){
        if(currentRoom->West!=NULL){
            currentRoom = currentRoom->West;
            printf("You are now in the %s.\n", currentRoom->name);
        }
        else{
            printf("You can't go west any further.\n");
        }
    }
    else{
        printf("That is not a directon. Try again:\n");
        char direction[10];
        scanf("%s", direction);
        go(direction);
    }
}