#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "level.h"

struct {
    unsigned int w : 1;
    unsigned int a : 1;
    unsigned int s : 1;
    unsigned int d : 1;
} keyState;

char *identifyKeyboardDevice();
/*void loadKeyState();*/
void loadLastKeyDown();
void onKeyDown(level *levelinfo, void (*func)(level*, int, int));

extern char *keyboardDevice;
extern char lastKeyDown;

#endif /* KEYBOARD_H */
