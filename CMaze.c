#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "helper.h"

int main() {
    boolean isEnd = false;
    boolean isRunning = true;

    while (isRunning == true) {
        
        welcomeMenu();
        char level = chooseLevel();
        clearScreen();

        readSize(level);
        char maze[size][size];
        readMaze(maze, level);
        printMaze(maze);
        
        while (isEnd == false)
            isEnd = playerMove(maze);

        isRunning = endScreen();

        if (isRunning == true)
            isEnd = false;

        clearScreen();
    }
    
    return 0;
}