#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H

#include "structs.h"

void alocMap (char path[], Map_t *map);

void lookingFor (Role_t *wizard, int which, Map_t *map);

int gameOver (Role_t *wizard, Map_t *map, float xo, float yo, int imageSizeX, int imageSizeY);

void spawnLightning(Map_t *map, int *score, int *missing);

void lookingForOgre(Ogre_t *character, int which, Map_t *map);

int hotDogCounter(Map_t *map);

void freeMap (Map_t *map);

#endif
