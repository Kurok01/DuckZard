#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "structs.h"

void initSDL ();

void initSound ();

void playSound ();

SDL_Texture *takeImage (char pathImage[]);

void makeTextures ();

int dragonSpawn(Map_t *map ,int *dragonCountDown, int *lightning, Role_t *wizard, Ogre_t ogres[], int beak, int qtd);

void stopTimeMode();

void printScreen (Map_t *map, Role_t *wizard, Ogre_t ogres[], int qtd ,int phase, int beak);

void freeSDL ();

#endif
