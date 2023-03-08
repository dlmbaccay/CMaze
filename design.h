#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void clearScreen() {
    system("cls");
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void colReset() {
    printf("\033[0;37m");
}

void colCyan() {
    printf("\033[0;36m");
}

void colBlue() {
    printf("\033[0;34m");
}

void colRed() {
    printf("\033[0;31m");
}

void colYellow() {
    printf("\033[0;33m");
}

void colGreen() {
    printf("\033[0;32m");
}

void colPurple(){
    printf("\033[0;35m");
}