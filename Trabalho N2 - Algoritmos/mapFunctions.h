#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H

#include "structs.h"

void alocMap (char path[], Map_t *map);

void lookingFor (Role_t *wizard, int which, Map_t *map);

void freeMap (Map_t *map);

#endif
