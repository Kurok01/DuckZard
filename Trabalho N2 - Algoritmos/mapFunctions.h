#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H

#include "structs.h"

void alocMap (char path[], Map_t *map);

void lookingFor (Wizard_t *wizard, int which, Map_t *map);

int gameOver (Wizard_t *wizard, Map_t *map, float xo, float yo, int imageSizeX, int imageSizeY);

void spawnLightning(Map_t *map, int *score, int *missing);

void freeze (Map_t *map, int blizzard);

void deFreeze (Map_t *map, Wizard_t *wizard, int fireDuration);

void lookingForMonster (Monster_t *monster, int which, Map_t *map);

int hotDogCounter(Map_t *map);

void freeMap (Map_t *map);

#endif
