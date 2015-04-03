#include "defs.h"
#include "keyboard.h"
#include "physics.h"

position playerPos;
position prevPlayerPos;

void playerSetup() {
    playerPos.x = prevPlayerPos.x = 0;
    playerPos.y = prevPlayerPos.y = 18;
}

void jump() {
    playerVelocityY = -2;
}

void updatePlayer() {
    if (keyState.w && playerPos.y == 18) {
        jump();
        /* jump or climb up ladder or something */
    } else if (keyState.s) {
        /* duck or climb down ladder or something */
    }

    if (keyState.d && playerPos.x < scrnWidth - 1) {
        playerPos.x++;
    } else if (keyState.a && playerPos.x > 0) {
        playerPos.x--;
    }
    updatePhysics();
}
