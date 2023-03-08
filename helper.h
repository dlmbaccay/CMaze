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

void readSize(char level) {
    FILE* mazeFile;
    if (level == 'E')
        mazeFile = fopen("EASYMAZE15.txt", "r");
    else if (level == 'M')
        mazeFile = fopen("MEDIUMMAZE25.txt", "r");
    else if (level == 'H')
        mazeFile = fopen("HARDMAZE25.txt", "r");
    fscanf(mazeFile, "%d", &size);
}

void readMaze(char maze[][size], char level) {

    FILE* mazeFile;

    if (level == 'E')
        mazeFile = fopen("EASYMAZE15.txt", "r");
    else if (level == 'M')
        mazeFile = fopen("MEDIUMMAZE25.txt", "r");
    else if (level == 'H')
        mazeFile = fopen("HARDMAZE25.txt", "r");

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
}

void printMaze(char maze[][size]) {  
    int wall, space; 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch(maze[j][i]) { // col x row
                case 'S':  
                    gotoxy((10+(i)*4) , (3+(j)*2)); colYellow(); printf("%c", 254); colReset();
                    break;
                case 'G': 
                    gotoxy((10+(i)*4) , (3+(j)*2)); colGreen(); printf("G"); colReset();
                    break;
                case '.': 
                    gotoxy((10+(i)*4) , (3+(j)*2)); printf("%c", 254);
                    break;
                case '#': 
                    gotoxy((10+(i)*4) , (3+(j)*2)); colRed(); printf("%c", 254); colReset();
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
            gotoxy((10+(temp[1])*4) , (3+(temp[0])*2)); printf("%c", 254);
            gotoxy((10+(currentPosition[1])*4) , (3+(currentPosition[0])*2)); colYellow(); printf("%c", 254); colReset();
            break;

        case 'G':
            maze[temp[0]][temp[1]] = '.';
            maze[currentPosition[0]][currentPosition[1]] = 'S';
            gotoxy((10+(temp[1])*4) , (3+(temp[0])*2)); printf("%c", 254);
            gotoxy((10+(currentPosition[1])*4) , (3+(currentPosition[0])*2)); colGreen(); printf("%c", 254); colReset();
            isEnd = true;
            break;
    }

    gotoxy(0,0);
    return isEnd;
}

void boxMaker(int tbLeft, int tbRight, int yTopHor, int yBotHor, int iLHor, int iRHor, int iLVer, int iRVer)
{
    gotoxy(tbLeft, yTopHor); printf("%c", 201); // top-left '╔'
    gotoxy(tbRight, yTopHor); printf("%c", 187); // top-right '╗'
    gotoxy(tbLeft, yBotHor); printf("%c", 200); // bottom-left '╚'
    gotoxy(tbRight, yBotHor); printf("%c", 188); // bottom-right '╝'
    
    for (int i = iLHor; i <= iRHor; i++) { 
        gotoxy(i, yTopHor); printf("%c", 205); // top horizontals '═'
        gotoxy(i, yBotHor); printf("%c", 205); // bottom horizontals '═'
    }

    for (int i = iLVer; i <= iRVer; i++) {
        gotoxy(tbLeft, i); printf("%c", 186); // left side vertical '║'
        gotoxy(tbRight, i); printf("%c", 186); // right side vertical '║'
    }
}

void welcomeMenu() {
    clearScreen();
    gotoxy(1, 1); colGreen(); printf("MAXIMIZE YOUR TERMINAL WINDOW!"); colReset();
    colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11); colReset();
    gotoxy(52,5); colYellow(); printf("TIC! TAC! TOE!");
    gotoxy(50,7); colRed(); printf("...find the goal!");
    gotoxy(54,9); colBlue(); printf("DEVELOPER:");
    gotoxy(48,10); colGreen(); printf("BACCAY, Dominic Luis M.");
    gotoxy(46,14); colCyan(); printf("*PRESS ANY KEY TO CONTINUE*");
    getch(); // awaits user input to continue to next function
}

char chooseLevel() {
    char command;
    do {
        clearScreen();
        colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11); colReset();
        gotoxy(50,5); colYellow(); printf("DETERMINE DIFFICULTY");
        gotoxy(51,7); colRed(); printf("...choose a level!");
        gotoxy(45,10); colGreen(); printf("[E] Easy [M] Medium] [H] Hard"); colReset();
        command = toupper(getch());
    } while (command != 'E' && command != 'M' && command != 'H');
    return command;
}

boolean endScreen() {
    char command;
    do {
        clearScreen();
        colCyan(); boxMaker(43, 75, 4, 12, 44, 74, 5, 11); colReset();
        gotoxy(53,5); colYellow(); printf("MAZE CLEARED");
        gotoxy(50,7); colRed(); printf("...congratulations!");
        gotoxy(49,10); colGreen(); printf("[X] Exit [R] Restart"); colReset();
        command = toupper(getch());

        if (command == 'X') 
            return false;
        else if (command == 'R') 
            return true;
    } while (command != 'E' && command != 'R');
}