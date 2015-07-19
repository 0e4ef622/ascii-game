#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#define scrnWidth 70
#define scrnHeight 20

typedef struct {
    int x;
    int y;
} position;

extern char lastKeyDown; /* removal is planned */
extern int kbdfd;

#endif
