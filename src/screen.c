#include <stdio.h>
#include <math.h>
#include <string.h>
#include "player.h"
#include "defs.h"

char screen[scrnWidth * scrnHeight];
int padding[2];

int coordToIndex(int x, int y) {
    return scrnWidth*y + x;
}

void drawBorder() {
    printf("\e[%d;%dH┌", padding[1]-1, *padding-1);

    int i;
    for (i = 0; i < scrnWidth; i++)
        printf("─");
    printf("┐");

    for (i = padding[1]; i < padding[1]+scrnHeight; i++) {
        printf("\e[%d;%dH│\e[%d;%dH│",i,*padding-1,i,*padding + scrnWidth);
    }
    printf("\e[%d;%dH└", padding[1]+scrnHeight, *padding-1);

    for (i = 0; i < scrnWidth; i++)
        printf("─");
    printf("┘");
}

void screenSetup(int cols, int rows) {
    *padding = cols/2 - scrnWidth/2;
    padding[1] = rows/2 - scrnHeight/2;

    printf("\e[2J\e[;H\e[?25l"); /* clear screen, move cursor to top left corner, hide cursor */

    drawBorder();

    memset(screen, ' ', scrnWidth * scrnHeight);
}

void drawPlayer() {
    screen[coordToIndex(prevPlayerPos.x, prevPlayerPos.y)] = ' ';
    screen[coordToIndex(playerPos.x, playerPos.y)] = '@';
}

void drawGround(int y) {
    int i;
    for (i = 0; i < scrnWidth; i++)
        screen[coordToIndex(i,y)] = '#';
}

void updateScreen() {
    drawPlayer();
}

void drawScreen() {
    int i, j;
    for (i = 0; i < scrnHeight; i++) {
        printf("\e[%d;%dH",i+padding[1],*padding);
        for (j = 0; j < scrnWidth; j++)
            printf("%c", screen[coordToIndex(j,i)]);
    }
}
