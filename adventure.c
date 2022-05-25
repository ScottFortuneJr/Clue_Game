#include <stdio.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include <stdlib.h>
#include <stdbool.h>

//initialize number of attempts
int tries = 0;

//command table
void command(char input[]){
    //help
    if(strcmp(input, "help") == 0){
        printf("\nhelp: list commands\nlist: list items, characters, and rooms\nlook: look around\n");
        printf("go: move into another room\ntake: grab an item\ndrop: drop an item\ninventory: check your inventory\n");
        printf("clue: make your guess\n");
    }
    //list
    else if(strcmp(input, "list") == 0){
        printf("\nitems: knife, gun, glass, guitar, wrench, sword\n");
        printf("characters: wife, husband, mechanic, cook, grandpa\n");
        printf("rooms: kitchen, attic, dining room, living room, master bedroom, guest bedroom, bathroom, pantry, garage\n");
    }
    //look
    else if(strcmp(input, "look") == 0){
        //print items in room
        printf("\nItems in rooms:\n");
        struct node* curr = location()->itemList->head;
        while(curr != NULL){
            printf("%s",curr->name);
            curr = curr->next;
        }

        //print characters
        printf("\nCharacters in room:\n%s\n", location()->character);

        //print adjacent rooms
        printf("Adjacent rooms:\n");
        if(location()->East != NULL){
            printf("east: %s\n", location()->East->name);
        }
        if(location()->North != NULL){
            printf("north: %s\n", location()->North->name);
        }
        if(location()->West != NULL){
            printf("west: %s\n", location()->West->name);
        }
        if(location()->South != NULL){
            printf("south: %s\n", location()->South->name);
        }
    }
    //go
    else if(strcmp(input, "go") == 0){
        printf("Type a cardinal direction to move to:\n");
        char direction[10];
        scanf("%s", direction);
        go(direction);
    }
    //take
    else if(strcmp(input, "take") == 0){
        printf("Select and item to pick up:\n");
        char itemToTake[19];
        scanf("%s", itemToTake);
        if(drop_item(location()->itemList, itemToTake) == -1) {
            printf("That item isn't in this room.\n");
        }
        else{
            add_item(getInventory(), itemToTake);
            printf("You picked up the %s.\n", itemToTake);
        }
    }
    //drop
    else if(strcmp(input, "drop") == 0){
        printf("Select an item from your inventory to drop:\n");
        char itemToDrop[19];
        scanf("%s", itemToDrop);
        if(drop_item(getInventory(), itemToDrop) == -1){
            printf("You do no have that item.\n");
        }
        else {
            add_item(location()->itemList, itemToDrop);
            printf("You dropped your %s in %s.\n", itemToDrop, location()->name);
        };
    }
    //inventory
    else if(strcmp(input, "inventory") == 0){
        struct node *curr = getInventory()->head;
        while(curr != NULL){
            printf("%s\n", curr->name);
            curr = curr->next;
        }
    }
    //clue
    else if(strcmp(input, "clue") == 0){
        char characterGuess[15];
        do{
            //get character input
            printf("Type the name of the murderer.\n");
            scanf("%s", characterGuess);
         //make sure input is ok
        }
        while(checkCharacterInput(characterGuess) == false);

        //find correct guesses
        bool cChar = guessChar(characterGuess);
        bool cItem = guessItem();
        bool cRoom = guessRoom();

        //declare victory
        if(cChar&&cItem&&cRoom){
            printf("YOU WON!\n");
            exit(0);
        }

        //print matches
        else{
            tries++;
            printf("Incorrect guess. Below are your matches(if any):\n");
            if(cChar){printf("Character match\n");};
            if(cItem){printf("Item match\n");};
            if(cRoom){printf("Room match\n");};
        }
    }
    //invalid command
    else{
        printf("%s is not a command. (type 'help' for a list of commands)\n",input);
    }
};

//main function
int main(int argc, char* argv[]) {
    //initialize iventory
    setUpInventory();

    //randomize rooms
    setUpRooms();

    //intro text
    printf("\n\nHello, welcome to Clue.\nYour task is to guess the killer, murder weapon, and scene of the crime by deduction.\n");
    printf("You are currently in the %s. What will you do?:\n", location()->name);

    //input while loop
    while(tries<10){
    char input[10];
    scanf("%10s", input);
    command(input);
    }

    //tries exceeded
    printf("You guessed wrong too many times.\nGAME OVER\n");
    return 0;
};