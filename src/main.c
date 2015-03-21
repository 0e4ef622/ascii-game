#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include "screen.h"
#include "canonctrl.h"
#include "keyboard.h"
#include "player.h"
#include "defs.h"

char *keyboardDevice;
int kbdfd;

int main(int argc, char **argv) {
    setbuf(stdout, NULL); /* disable output buffering */
    fcntl(0, F_SETFL, O_NONBLOCK); /* nonblock stdin read */
    termNonCanon(); /* set terminal to non canonical and dont echo input (see canonctrl.c) */

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    /* do setup stuff */

    screenSetup(w.ws_col, w.ws_row);
    playerSetup();

    keyboardDevice = identifyKeyboardDevice();
    if (keyboardDevice == NULL) return 1;
    kbdfd = open(keyboardDevice, O_RDONLY | O_NONBLOCK);

    drawGround(19); /* drawGround function is temporary and will likely not exist once level file reading is implemented */

    char k;
    while (1) {
        loadKeyState();
        updatePlayer();

        updateScreen();
        drawScreen();

        loadLastKeyDown();
        if (lastKeyDown == 'q') break; /* this will likely change */

        prevPlayerPos.x = playerPos.x;
        prevPlayerPos.y = playerPos.y;
        usleep(30000);
    }

    printf("\e[?25h"); /* unhide cursor */
    termReset(); /* set terminal back to normal */

    return 0;
}
