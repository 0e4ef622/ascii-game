#include "level.h"

#ifndef SCREEN_H
#define SCREEN_H

void screenSetup(int rows, int cols);
void drawPlayer();
void updateScreen();
void drawScreen();
void loadLevel(level *levelinfo);
int coordToIndex(int x, int y);

#endif /* SCREEN_H */
