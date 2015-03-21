#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <linux/input.h>
#include "defs.h"

char lastKeyDown; /* removal is planned */

char *identifyKeyboardDevice() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/dev/input/by-id")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            /* do stuff */
            char *name = ent->d_name;
            int nameLen = strlen(name);

            char *lastPart = name + nameLen - 9;

            if (!strcmp(lastPart,"event-kbd")) {
                char *path = (char *) malloc(18 + nameLen);
                strcat(path,"/dev/input/by-id/");
                closedir(dir);
                return strcat(path, name);
            }
        }
        printf("Could not identify keyboard device\n");
        return NULL;
    } else {
        printf("Could not open directory /dev/input/by-id\n");
        return NULL;
    }
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
