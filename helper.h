#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "design.h"

typedef enum {
    true, false
} boolean;

int size;
int goalPosition[2];
int currentPosition[2];

void readSize() {
    FILE* mazeFile;
    mazeFile = fopen("maze.txt", "r");
    fscanf(mazeFile, "%d", &size);
}

void readMaze(char maze[][size]) {
    FILE* mazeFile;

    mazeFile = fopen("maze.txt", "r");

    fscanf(mazeFile, "%d", &size);
    char boardLineInput[size];
    
    for (int i = 0; i < size; i++) {
        fscanf(mazeFile, "%s", boardLineInput);
        for (int j = 0; j < size; j++) {
            maze[i][j] = boardLineInput[j];
        }
    }

    fclose(mazeFile);

    for (int i = 0; i < size; i++) { // search for start and goal positions
        for (int j = 0; j < size; j++) {
            if (maze[i][j] == 'S') {
                currentPosition[0] = i;
                currentPosition[1] = j;
            } else if (maze[i][j] == 'G') {
                goalPosition[0] = i;
                goalPosition[1] = j;
            }
        }
    }

    printf("Goal: %d, %d\n", goalPosition[0], goalPosition[1]);
    printf("Current: %d, %d\n", currentPosition[0], currentPosition[1]);
}

void printMaze(char maze[][size]) {  
    int wall, space; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch(maze[j][i]) { // col x row
                case 'S':  
                    gotoxy((10+(i)*4) , (5+(j)*2)); colYellow(); printf("%c", 254); colReset();
                    break;
                case 'G': 
                    gotoxy((10+(i)*4) , (5+(j)*2)); colGreen(); printf("G"); colReset();
                    break;
                case '.': 
                    gotoxy((10+(i)*4) , (5+(j)*2)); printf("%c", 254);
                    break;
                case '#': 
                    gotoxy((10+(i)*4) , (5+(j)*2)); colRed(); printf("%c", 254); colReset();
                    break;
            }
        }
    }

    gotoxy(0,0);
}

boolean playerMove(char maze[][size]) {
    boolean isEnd = false;
    int temp[2];
    temp[0] = currentPosition[0];
    temp[1] = currentPosition[1];

    switch (toupper(getch())) {
        case 'W': 
            if (currentPosition[0] - 1 >= 0 && maze[currentPosition[0] - 1][currentPosition[1]] != '#')
                currentPosition[0] -= 1;
            break;
        case 'A':
            if (currentPosition[1] - 1 >= 0 && maze[currentPosition[0]][currentPosition[1] - 1] != '#')
                currentPosition[1] -= 1;
            break;
        case 'S':
            if (currentPosition[0] + 1 < size && maze[currentPosition[0] + 1][currentPosition[1]] != '#')
                currentPosition[0] += 1;
            break;
        case 'D':
            if (currentPosition[1] + 1 < size && maze[currentPosition[0]][currentPosition[1] + 1] != '#')
                currentPosition[1] += 1;
            break;
    }

    switch(maze[currentPosition[0]][currentPosition[1]]) {
        case '.': 
            maze[temp[0]][temp[1]] = '.';
            maze[currentPosition[0]][currentPosition[1]] = 'S';
            break;

        case 'G':
            maze[temp[0]][temp[1]] = '.';
            maze[currentPosition[0]][currentPosition[1]] = 'S';
            isEnd = true;
            break;
    }

    gotoxy(0,0);
    return isEnd;
}