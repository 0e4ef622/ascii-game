#ifndef KEYBOARD_H
#define KEYBOARD_H

struct {
    unsigned int w : 1;
    unsigned int a : 1;
    unsigned int s : 1;
    unsigned int d : 1;
} keyState;

char *identifyKeyboardDevice();
void loadKeyState();
void loadLastKeyDown();

extern char *keyboardDevice;
extern char lastKeyDown;

#endif /* KEYBOARD_H */
