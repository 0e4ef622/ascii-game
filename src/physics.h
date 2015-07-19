#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "level.h"

void updatePhysics();
int collision(level *levelinfo, int x, int y, int dir);

extern float playerVelocityY;

#endif /* GAME_PHYSICS_H */
