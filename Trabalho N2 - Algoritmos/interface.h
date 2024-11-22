#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "structs.h"

SDL_DisplayMode displayMode;

SDL_Renderer *renderer;

SDL_Window *window;

void initSDL ();

void initSound ();

void playSound ();

SDL_Texture *takeImage (char pathImage[]);

void makeTextures ();

void phase2ElementsSpawn (Map_t *map, int *blizzard, Wizard_t *wizard, Monster_t *monster, int beak, int qtd);

void spawnFire (Map_t *map, int direction, float x, float y);

int phase1ElementsSpawn (Map_t *map, int *dragonCountDown, int *lightning, Wizard_t *wizard, Monster_t *monster, int beak, int qtd);

void stopTimeMode();

void printScreen (Map_t *map, Wizard_t *wizard, Monster_t monster[], int qtd ,int phase, int beak);

void freeSDL ();

#endif
