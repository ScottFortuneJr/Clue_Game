
To Compile: gcc items.c adventure.c rooms.c -o test -Wall
./test


Overview/Project Requirements(following the rubric)
    a. in rooms.c, the Room struct has pointers to adjacent rooms and the rooms are arranged in a 3x3 pattern. At the bottom of setUpRooms, the pointers are set based on room
        location.
    b. in rooms.c setUpRooms() under the item initialization steps, an array of random integers from 0 to 8 is created. This array is used against the room array to keep the 3x3
        pattern while still using randomness.
    c. in rooms.c setUpRooms() at the top, the items are allocated, added to lists, and assigned to their respective rooms. The characters are assigned as strings to rooms,
        and each room gets at most one item.
    d. in rooms.c setUpRooms() towards the middle, the trio of correct answers are picked randomly using rand() and their respective arrays
    e. the struct and functions for linked lists are in items.c and are assigned to rooms in rooms.c
    f. in items.c under the struct definitions, the inventory is created and functions for using it.
    g. in adventure.c, the user input is passed to command() and the command that matches the string is run.
    h. in adventure.c command() for "clue", the game checks the current room, character, and items in the inventory and room, and compares them to the correct answers. An
        incorrect guess incraments the tries counter. The counter is checked after each loop in main and the game ends after 10 wrong answers.
    i.rooms.c, items.c, and adventure.c are setup accordingly
