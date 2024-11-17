#ifndef ACTIONS_H
#define ACTIONS_H

int move (const Uint8 *state, Role_t *wizard, Map_t *map, Uint32 *lastTIME, Ogre_t *ogre);

void eat(Map_t *map, Role_t *wizard, int *score, int *missing);

int moveNPC(Map_t *map, Ogre_t *character, Uint32 *lastTIME, Role_t *wizard);

#endif
