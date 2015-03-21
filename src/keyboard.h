#ifndef KEYBOARD_H
#define KEYBOARD_H

char *identifyKeyboardDevice();
void loadKeyState();
void loadLastKeyDown();

extern char *keyboardDevice;
extern char lastKeyDown;

#endif /* KEYBOARD_H */
