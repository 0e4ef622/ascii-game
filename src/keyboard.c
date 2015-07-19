#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include "keyboard.h"
#include "defs.h"

char lastKeyDown; /* removal is planned */

char *identifyKeyboardDevice() {
    char *buf = (char *) malloc(1024);
    char *buf2 = (char *) malloc(1024);
    char *buf3 = (char *) malloc(1024);
    char *ptr = buf;

    int findEvent = 0;

    char *template = (char *) malloc(19);
    strcpy(template, "/dev/input/");

    int fd = open("/proc/bus/input/devices", O_RDONLY);
    while (read(fd, ptr, 1)) {
        if (*ptr == '\n') {
            *ptr = 0;

            if (strstr(buf,"EV=120013") || strstr(buf,"EV=12001f")) {
                ptr = strstr(buf3,"event");
                char a[8] = "event";

                int i;
                int verified = 1;
                for (i = 0; i < 5; i++) {
                    if (a[i] != ptr[i]) {
                        verified = 0;
                        break;
                    }
                }

                if (!verified) continue;

                char c;
                while ((c=ptr[i]) != ' ' && c != '\n')
                    a[i++] = c;

                strcat(template, a);
                free(buf);
                free(buf2);
                free(buf3);
                return template;
            }
            char *tmp = buf;
            /* switch make buf2 buf, buf3 buf2 and buf buf3 */
            buf = buf3;
            buf3 = buf2;
            buf2 = tmp;

            ptr = buf;
        } else {
            ptr++;
        }
    }
    close(fd);

    free(buf);
    free(buf2);
    free(buf3);

    fprintf(stderr, "Could not autodetect keyboard\n");
    return NULL;

}

void loadKeyState() {
    char keymp[KEY_MAX/8 + 1];

    memset(keymp, 0, sizeof(keymp));

    ioctl(kbdfd, EVIOCGKEY(sizeof(keymp)), keymp);

    int keys[4] = {KEY_W, KEY_A, KEY_S, KEY_D};

    int i;
    for (i=0;i<4;i++) {
        int key = keys[i];
        int keyb = keymp[key/8];
        int mask = 1 << (key % 8);
        keys[i] = !!(keyb & mask);
    }

    keyState.w = keys[0];
    keyState.a = keys[1];
    keyState.s = keys[2];
    keyState.d = keys[3];
}

void loadLastKeyDown() {
    char a;
    char b;

    ssize_t retval = read(0, &a, 1);
    while (retval != -1) {
        b = a;
        retval = read(0, &a, 1);
    }

    lastKeyDown = b;
}
