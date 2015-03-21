#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include <stdio.h>

#define scrnWidth 70
#define scrnHeight 20

typedef struct {
    int x;
    int y;
} position;

struct {
    unsigned int w : 1;
    unsigned int a : 1;
    unsigned int s : 1;
    unsigned int d : 1;
} keyState;

extern char lastKeyDown; /* removal is planned */
extern int kbdfd;

#endif
