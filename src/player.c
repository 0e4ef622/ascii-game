#include "defs.h"
#include "keyboard.h"

position playerPos;
position prevPlayerPos;

void playerSetup() {
    playerPos.x = prevPlayerPos.x = 0;
    playerPos.y = prevPlayerPos.y = 18;
}

void updatePlayer() {
    if (keyState.w) {
        /* jump or climb up ladder or something */
    } else if (keyState.s) {
        /* duck or climb down ladder or something */
    }

    if (keyState.d && playerPos.x < scrnWidth - 1) {
        playerPos.x++;
    } else if (keyState.a && playerPos.x > 0) {
        playerPos.x--;
    }
}
