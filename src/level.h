#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

typedef struct {
    int width;
    int height;
    char *data;
} level;

level *getLevelFromFile(char *levelFile);

#endif /* GAME_LEVEL_H */
