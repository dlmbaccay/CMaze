#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "helper.h"

boolean isEnd = false;

int main() {

    readSize();
    char maze[size][size];
    readMaze(maze);
    
    while (isEnd == false) {
        printMaze(maze);
        isEnd = playerMove(maze);
    }

    // printMaze(maze); // testing
    testPrint(maze);

    getch(); // press any key to exit terminal
    system("cls");
    return 0;
}

void initializeMaze() {
    
}
