#include <linux/input.h>
#include "defs.h"
#include "keyboard.h"
#include "physics.h"
#include "level.h"
#include "constants.h"

position playerPos;
position prevPlayerPos;

void jump() {
    playerVelocityY = -2;
}

void keyEvHandler(level *levelinfo, int key, int val) {
    if (key == KEY_W && val != 2) {
        keyState.w = val;
        if (val && collision(levelinfo, playerPos.x, playerPos.y, DOWN))/* && playerVelocityY == 0)*/
            jump();
    }
    else if (key == KEY_A && val != 2) keyState.a = val;
    else if (key == KEY_S && val != 2) keyState.s = val;
    else if (key == KEY_D && val != 2) keyState.d = val;
}

void playerSetup(level *levelinfo) {
    playerPos.x = prevPlayerPos.x = 0;
    playerPos.y = prevPlayerPos.y = 18;
    onKeyDown(levelinfo, &keyEvHandler);
}

void updatePlayer(level *levelinfo) {
    if (keyState.w && collision(levelinfo, playerPos.x, playerPos.y, DOWN)) {
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
