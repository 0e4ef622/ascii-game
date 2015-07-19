#include "defs.h"
#include "keyboard.h"
#include "physics.h"
#include "level.h"
#include "constants.h"

position playerPos;
position prevPlayerPos;

void playerSetup() {
    playerPos.x = prevPlayerPos.x = 0;
    playerPos.y = prevPlayerPos.y = 18;
}

void jump() {
    playerVelocityY = -2;
}

void updatePlayer(level *levelinfo) {
    if (keyState.w && collision(levelinfo, playerPos.x, playerPos.y, DOWN) && playerVelocityY == 0) {
        jump();
        /* jump or climb up ladder or something */
    } else if (keyState.s) {
        /* duck or climb down ladder or something */
    }

    if (keyState.d && playerPos.x < scrnWidth - 1) {
        if (!collision(levelinfo, playerPos.x, playerPos.y, RIGHT))
            playerPos.x++;
    } else if (keyState.a && playerPos.x > 0) {
        if (!collision(levelinfo, playerPos.x, playerPos.y, LEFT))
            playerPos.x--;
    }
    updatePhysics(levelinfo);
}
