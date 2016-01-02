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
#include "level.h"
#include "errnomsg.h"

char *keyboardDevice;
int kbdfd;

void cleanup() {
    printf("\e[?25h\e[2J\e[;H"); /* unhide cursor, clear screen, move cursor to top left corner */
    termReset(); /* set terminal back to normal */
}

int main(int argc, char **argv) {

    /* get a level information from a file */

        level *levelinfo = getLevelFromFile((argc < 2) ? "testfile" : argv[1]);
    if (levelinfo == NULL) {
        return 1;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    /* check terminal size */

    if (w.ws_col < scrnWidth+2 || w.ws_row < scrnHeight+2) {
        printf("Terminal is too small. Are you sure you want to continue? [y/n]: ");
        char c = getchar();
        if (c != 'y' && c != 'y') return 1;
    }

    /* autodetect keyboard device */

    keyboardDevice = identifyKeyboardDevice();
    if (keyboardDevice == NULL) return 1;
    kbdfd = open(keyboardDevice, O_RDONLY | O_NONBLOCK);

    if (kbdfd == -1) {
        errno_msg(keyboardDevice);
        return 1;
    }

    setbuf(stdout, NULL); /* disable stdout buffering */

    termSetup(); /* setup terminal (obviously) */
    fcntl(0, F_SETFL, O_NONBLOCK); /* nonblock stdin read */

    /* more setup */

    screenSetup(w.ws_col, w.ws_row);
    playerSetup(levelinfo);

    loadLevel(levelinfo);

    char exit_reason = 0; /* 0 is quit, 1 is player haxed out of border, 2 is player fell to death */
    while (1) {
        /*loadKeyState();*/
        updatePlayer(levelinfo);
        if (playerPos.x < 0 || playerPos.x > scrnWidth || playerPos.y < 0) {
            exit_reason = 1;
            break;
        } else if (playerPos.y > scrnHeight) {
            exit_reason = 2;
            break;
        }

        updateScreen();
        drawScreen();

        loadLastKeyDown();
        if (lastKeyDown == 'q') break;

        prevPlayerPos.x = playerPos.x;
        prevPlayerPos.y = playerPos.y;
        usleep(30000);
    }

    cleanup();
    switch (exit_reason) {
        case 0:
            break;
        case 1:
            printf("How'd you hax thru duh borderz das not supposed to happen\n");
            break;
        case 2:
            printf("You fell to your death.\n");
            break;
        default:
            printf("Something terribly wrong happened.\n");
    }

    return 0;
}
