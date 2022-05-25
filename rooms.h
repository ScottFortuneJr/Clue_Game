#ifndef ROOMS_H_
#define ROOMS_H_
#include <stdbool.h>

struct Room *location();
bool checkCharacterInput();
bool guessRoom();
bool guessChar();
bool guessItem();
void setUpRooms();
void go(char[10]);
struct Room {
    char name[30];
    char character[50];
    struct list * itemList;
    struct Room * North;
    struct Room * South;
    struct Room * East;
    struct Room * West;
};

#endif