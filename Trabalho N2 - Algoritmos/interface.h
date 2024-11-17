#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h>
#include "structs.h"

void initSDL ();

SDL_Texture *takeImage (char pathImage[]);

void makeTextures ();

void printScreen (Map_t *map, Role_t *wizard, Role_t ogres[], int qtd, int phase, int beak, int *dragonCountDown);

void freeSDL ();

#endif
