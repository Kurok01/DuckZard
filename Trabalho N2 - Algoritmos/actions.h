#ifndef ACTIONS_H
#define ACTIONS_H

void move (const Uint8 *state, Role_t *wizard, Map_t *map, Uint32 *lastTIME);

void eat(Map_t *map, Role_t *wizard, int *score, int *missing);

void moveNPC(Map_t *map, Ogre_t *character, Uint32 *lastTIME);

#endif
