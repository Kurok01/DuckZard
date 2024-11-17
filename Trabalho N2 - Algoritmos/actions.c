#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "mapFunctions.h"
#include "structs.h"

#define MOVESPEED 150
#define MOVESPEEDNPC 100

void move (const Uint8 *state, Role_t *wizard, Map_t *map, Uint32 *lastTIME) {
	
	float speedX = 0, speedY = 0;
	float preX = wizard->x, preY = wizard->y;
	int xD, yD, x, y;
	int i;
	char limits[] = "*$";
	
	if (state[SDL_SCANCODE_W]) {
		
		speedY = -MOVESPEED;
		wizard->direction = 3;
	} 
	
	if (state[SDL_SCANCODE_S]) {
		
		speedY = +MOVESPEED;
		wizard->direction = 2;
	}
	 
	if (state[SDL_SCANCODE_A]) {
		
		speedX = -MOVESPEED;
		wizard->direction = 1;
	}
	 
	if (state[SDL_SCANCODE_D]) {
		
		speedX = +MOVESPEED;
		wizard->direction = 0;
	}
	
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - *lastTIME) / 1000.00;
	*lastTIME = currentTime;
	
	wizard->x += (speedX * deltaTime);
	wizard->y += (speedY * deltaTime);
	
	xD = (((wizard->x + map->imageSize - 4) - map->outOfLimitsX) / map->imageSize);
	yD = (((wizard->y + map->imageSize - 4) - map->outOfLimitsY) / map->imageSize);
	
	x = ((wizard->x - map->outOfLimitsX + 4)/ map->imageSize);
	y = ((wizard->y - map->outOfLimitsY + 4) / map->imageSize);
	
	for(i = 0; i < 2; i++){
		if (map->mapPptr[y][x] == limits[i] || map->mapPptr[yD][xD] == limits[i] || map->mapPptr[y][xD] == limits[i] || map->mapPptr[yD][x] == limits[i]) {
			
			wizard->x = preX;
			wizard->y = preY;
			break;
		}
	}
}

void eat (Map_t *map, Role_t *wizard, int *score, int *missing) {
	
	int x, y, xD, yD;
	
	xD = (((wizard->x + map->imageSize - 8) - map->outOfLimitsX) / map->imageSize);
	yD = (((wizard->y + map->imageSize - 8) - map->outOfLimitsY) / map->imageSize);
	
	x = ((wizard->x - map->outOfLimitsX + 8)/ map->imageSize);
	y = ((wizard->y - map->outOfLimitsY + 8) / map->imageSize);
	
	if (map->mapPptr[y][x] == ' '){
		
		map->mapPptr[y][x] = '-';
		
		(*score)++;
		(*missing)--;
	}
	
	if (map->mapPptr[y][xD] == ' '){
		
		map->mapPptr[y][xD] = '-';
		
		(*score)++;
		(*missing)--;
		
	}
	
	if (map->mapPptr[yD][x] == ' '){
		
		map->mapPptr[yD][x] = '-';
		
		(*score)++;
		(*missing)--;
		
	}
	
	if (map->mapPptr[yD][xD] == ' '){
		
		map->mapPptr[yD][xD] = '-';
		
		(*score)++;
		(*missing)--;
	}
}

void moveNPC(Map_t *map, Role_t *character, Uint32 *lastTIME){

	float speedX, speedY;
	float preX = character->x, preY = character->y;
	int xD, yD, x, y;
	int i;
	char limits[] = "*$";
	
	switch(character->direction) {
		
		case 0:
			speedX = +MOVESPEEDNPC;
			break;
			
		case 1:
			speedX = -MOVESPEEDNPC;
			break;
			
		case 2:
			speedY = +MOVESPEEDNPC;
			break;
			
		case 3:
			speedY = -MOVESPEEDNPC;
			break;
	}	

	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - *lastTIME) / 1000.00;
	*lastTIME = currentTime;
	
	character->x += (speedX * deltaTime);
	character->y += (speedY * deltaTime);
	
	xD = (((character->x + map->imageSize + 4) - map->outOfLimitsX) / map->imageSize);
	yD = (((character->y + map->imageSize - 4) - map->outOfLimitsY) / map->imageSize);
	
	x = ((character->x - map->outOfLimitsX + 4)/ map->imageSize);
	y = ((character->y - map->outOfLimitsY + 4) / map->imageSize);
	
	for(i = 0; i < 2; i++){
		
		if (map->mapPptr[y][x] == limits[i] || map->mapPptr[yD][xD] == limits[i] || map->mapPptr[y][xD] == limits[i] || map->mapPptr[yD][x] == limits[i]) {
			
			character->x = preX;
			character->y = preY;
			break;
		}
	}
}
