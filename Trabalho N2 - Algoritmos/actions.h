#ifndef ACTIONS_H
#define ACTIONS_H

void move (const Uint8 *state, Wizard_t *wizard, Map_t *map, Uint32 *lastTIME, int MOVESPEED);

void reverseMoves(const Uint8 *state, Wizard_t *wizard, Map_t *map, Uint32 *lastTIME, int MOVESPEED);

void eatPill(Map_t *map, Wizard_t *wizard, int *lightning);

void eat(Map_t *map, Wizard_t *wizard, int *score, int *missing);

void moveNPC(Map_t *map, Monster_t *character, Wizard_t *wizard,Uint32 *lastTIME, int MOVESPEED);

void spawnClone(Map_t *map, Monster_t *clone, int *numClones, int phase);

#endif
