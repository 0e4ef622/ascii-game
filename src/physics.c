#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "defs.h"
#include "constants.h"
#include "level.h"

#define GRAVITY .4 /* characters per 30,000 microseconds squared */

float precisePlayerPosY = 18;
float playerVelocityY = 0;

void updatePhysics(level *levelinfo) {

    precisePlayerPosY += playerVelocityY;

    int i, y, collide = 0;
    int diff = precisePlayerPosY - playerPos.y;

    for (i = 0; i < abs(diff); i++) {

        y = playerPos.y + (diff & -2147483648 | 1)*i;
        int dir = (diff < 0) ? UP : DOWN;

        if (collision(levelinfo, playerPos.x, y, dir)) {
            collide = 1;
            break;
        }

    }

    if (collide) {

        precisePlayerPosY = y;
        playerPos.y = y;
        playerVelocityY = 0;

    } else
        playerVelocityY += GRAVITY;

    playerPos.y = precisePlayerPosY;
}

int collision(level *levelinfo, int x, int y, int dir) {
    int ret = 0;
    if (dir & UP) {
        int i = coordToIndex(x, y-1);
        if (levelinfo->data[i] == '#') ret = ret | UP;
    } else if (dir & DOWN) {
        int i = coordToIndex(x, y+1);
        if (levelinfo->data[i] == '#') ret = ret | DOWN;
    } else if (dir & LEFT) {
        int i = coordToIndex(x-1, y);
        if (levelinfo->data[i] == '#') ret = ret | LEFT;
    } else if (dir & RIGHT) {
        int i = coordToIndex(x+1, y);
        if (levelinfo->data[i] == '#') ret = ret | RIGHT;
    } else {
        fprintf(stderr, "Some idiot screwed up trying to call collision() which is defined in physics.c\n");
    }
    return ret;
}
