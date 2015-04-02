#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "screen.h"
#include "canonctrl.h"
#include "keyboard.h"
#include "player.h"
#include "defs.h"

char *keyboardDevice;
int kbdfd;

int main(int argc, char **argv) {

    /* autodetect keyboard device */

    keyboardDevice = identifyKeyboardDevice();
    if (keyboardDevice == NULL) return 1;
    kbdfd = open(keyboardDevice, O_RDONLY | O_NONBLOCK);

    if (errno == EACCES) {
       fprintf(stderr, "Permission denied when attempting to open file:\n%s\nDid you run ./configure or are you root?\n", keyboardDevice);
       return 1;
    }

    setbuf(stdout, NULL); /* disable stdout buffering */

    termSetup(); /* setup terminal (obviously) */
    fcntl(0, F_SETFL, O_NONBLOCK); /* nonblock stdin read */

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    /* do setup stuff */

    screenSetup(w.ws_col, w.ws_row);
    playerSetup();

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

    printf("\e[?25h\e[2J\e[;H"); /* unhide cursor, clear screen, move cursor to top left corner */
    termReset(); /* set terminal back to normal */

    return 0;
}
