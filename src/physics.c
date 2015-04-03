#include "player.h"
#include "defs.h"

#define GRAVITY .4 /* characters per second squared */

float precisePlayerPosY = 18;
float playerVelocityY = 0;

void updatePhysics() {
    /* TODO collision detection rather than ground detection */
    if ((precisePlayerPosY+=playerVelocityY) > 18) {
        precisePlayerPosY = 18;
        playerVelocityY = 0;
    } else {
        playerVelocityY += GRAVITY;
    }
    playerPos.y = precisePlayerPosY;
}
