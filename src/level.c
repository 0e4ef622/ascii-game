#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "level.h"
#include "defs.h"
#include "errnomsg.h"

level levelinfo;

level *getLevelFromFile(char *levelFile) {
    FILE *lvlptr = fopen(levelFile, "r");

    if (lvlptr == NULL) {
        errno_msg(levelFile);
        return NULL;
    }

    char header[6];
    fread(header, 1, 5, lvlptr);
    if (strcmp(header, "hello")) {
        fclose(lvlptr);
        fprintf(stderr, "Invalid level file\n");
        return NULL;
    }

    fread(&(levelinfo.width), 2, 1, lvlptr);
    fread(&(levelinfo.height), 2, 1, lvlptr);

    int len = levelinfo.width * levelinfo.height;
    levelinfo.data = (char *) malloc(len);
    char *p = levelinfo.data;
    char d;
    int i = 0;
    while ((d = fgetc(lvlptr)) != EOF && i < len) {
        if (d != '\n') {
            *(p++) = d;
            i++;
        }
    }

    fclose(lvlptr);

    return &levelinfo;
}
