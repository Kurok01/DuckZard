#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "mapFunctions.h"
#include "structs.h"

#define MOVESPEEDNPC 100

void move (const Uint8 *state, Role_t *wizard, Map_t *map, Uint32 *lastTIME, int MOVESPEED) {
	
	float speedX = 0, speedY = 0;
	float preX = wizard->x, preY = wizard->y;
	int xD, yD, x, y;
	int i;
	char limits[] = "*$ASV";
	
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
	
	xD = (((wizard->x + map->imageSize - 5) - map->outOfLimitsX) / map->imageSize);
	yD = (((wizard->y + map->imageSize - 5) - map->outOfLimitsY) / map->imageSize);
	
	x = ((wizard->x - map->outOfLimitsX + 5)/ map->imageSize);
	y = ((wizard->y - map->outOfLimitsY + 5) / map->imageSize);
	
	for (i = 0; i < 5; i++) {
		
		if (map->mapPptr[y][x] == limits[i] || map->mapPptr[yD][xD] == limits[i] || map->mapPptr[y][xD] == limits[i] || map->mapPptr[yD][x] == limits[i]) {
			
			wizard->x = preX;
			wizard->y = preY;
			break;
		}
		
	}
}

void reverseMoves(const Uint8 *state, Role_t *wizard, Map_t *map, Uint32 *lastTIME, int MOVESPEED) {
	
	float speedX = 0, speedY = 0;
	float preX = wizard->x, preY = wizard->y;
	int xD, yD, x, y;
	int i;
	char limits[] = "*$ASV";
	
	if (state[SDL_SCANCODE_W]) {
		
		speedY = +MOVESPEED;
		wizard->direction = 2;
	} 
	
	if (state[SDL_SCANCODE_S]) {
		
		speedY = -MOVESPEED;
		wizard->direction = 3;
	}
	 
	if (state[SDL_SCANCODE_A]) {
		
		speedX = +MOVESPEED;
		wizard->direction = 0;
	}
	 
	if (state[SDL_SCANCODE_D]) {
		
		speedX = -MOVESPEED;
		wizard->direction = 1;
	}
	
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - *lastTIME) / 1000.00;
	*lastTIME = currentTime;
	
	wizard->x += (speedX * deltaTime);
	wizard->y += (speedY * deltaTime);
	
	xD = (((wizard->x + map->imageSize - 5) - map->outOfLimitsX) / map->imageSize);
	yD = (((wizard->y + map->imageSize - 5) - map->outOfLimitsY) / map->imageSize);
	
	x = ((wizard->x - map->outOfLimitsX + 5)/ map->imageSize);
	y = ((wizard->y - map->outOfLimitsY + 5) / map->imageSize);
	
	for (i = 0; i < 5; i++) {
		
		if (map->mapPptr[y][x] == limits[i] || map->mapPptr[yD][xD] == limits[i] || map->mapPptr[y][xD] == limits[i] || map->mapPptr[yD][x] == limits[i]) {
			
			wizard->x = preX;
			wizard->y = preY;
			break;
		}
		
	}
}


void eatPill(Map_t *map, Role_t *wizard, int *lightning){
	int xD, yD, x, y;
	
	xD = (((wizard->x + map->imageSize - 5) - map->outOfLimitsX) / map->imageSize);
	yD = (((wizard->y + map->imageSize - 5) - map->outOfLimitsY) / map->imageSize);
	
	x = ((wizard->x - map->outOfLimitsX + 5)/ map->imageSize);
	y = ((wizard->y - map->outOfLimitsY + 5) / map->imageSize);
	
	if (map->mapPptr[y][x] == '+' || map->mapPptr[yD][xD] == '+' || map->mapPptr[y][xD] == '+' || map->mapPptr[yD][x] == '+') {
		
		
	if(map->mapPptr[y][x] == '+') map->mapPptr[y][x] = ' ';
	if(map->mapPptr[yD][xD] == '+') map->mapPptr[yD][xD] = ' ';
	if(map->mapPptr[y][xD] == '+') map->mapPptr[y][xD] = ' ';
	if(map->mapPptr[yD][x] == '+') map->mapPptr[yD][x] = ' ';
		
	(*lightning) = 1;
	playSound(4);
	
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
		
		playSound(2);
		(*score)++;
		(*missing)--;
	}
	
	if (map->mapPptr[y][xD] == ' '){
		
		map->mapPptr[y][xD] = '-';
		
		playSound(2);
		(*score)++;
		(*missing)--;
		
	}
	
	if (map->mapPptr[yD][x] == ' '){
		
		map->mapPptr[yD][x] = '-';
		
		playSound(2);
		(*score)++;
		(*missing)--;
		
	}
	
	if (map->mapPptr[yD][xD] == ' '){
		
		map->mapPptr[yD][xD] = '-';
		
		playSound(2);
		(*score)++;
		(*missing)--;
		
	}
}

void moveNPC(Map_t *map, Ogre_t *character, Role_t *wizard,Uint32 *lastTIME, int MOVESPEED) {
		
	float speedX = 0, speedY = 0;
	float preX = character->x, preY = character->y;
	int matrizXO, matrizYO, matrizXD, matrizYD;
	int matrizXOU, matrizYOU, matrizXOT, matrizYOT;
	int prematrizXOU, prematrizYOU, prematrizXOT, prematrizYOT;
	int correct = 1, correctGPS = 1, aux, aux2, direction = 0;
	int i, j;
	char limits[] = "*$ASV";
	
	srand(time(0));
	
	matrizXD = ((wizard->x + (map->imageSize/2)) - map->outOfLimitsX) / map->imageSize;
	matrizYD = ((wizard->y + (map->imageSize/2)) - map->outOfLimitsY) / map->imageSize;
	
	matrizXO = ((character->x + (map->imageSize/2)) - map->outOfLimitsX) / map->imageSize;
	matrizYO = ((character->y + (map->imageSize/2)) - map->outOfLimitsY) / map->imageSize;
	
	aux = matrizXO;
	aux2 = matrizYO;
	
	for(i = 0; i < 8; i++){
		
		for(j = 0; j < 5; j++){
			if(map->mapPptr[aux2][aux] == limits[j]){
				correctGPS = 0;
				break;
			}
		}
		
		if(aux < matrizXD && (aux + 8) < matrizXD) correctGPS = 0;
		else if(aux > matrizXD && (aux - 8) > matrizXD) correctGPS = 0;
		if(aux2 < matrizYD && (aux2 + 8) < matrizYD) correctGPS = 0;
		else if(aux2 > matrizYD && (aux2 - 8) > matrizYD) correctGPS = 0;
		
		if(correctGPS == 0) break;
		
		
		if(aux < matrizXD) aux++;
		else if(aux > matrizXD) aux--;
		else if(aux2 < matrizYD) aux2++;
		else if(aux2 > matrizYD) aux2--;
		
	}
	
	
	
	if(correctGPS == 1){
		
		if(matrizYO < matrizYD) character->destY = (matrizYD * map->imageSize) + map->outOfLimitsY;
		if(matrizXO < matrizXD) character->destX = (matrizXD * map->imageSize) + map->outOfLimitsX;
		if(matrizYO > matrizYD) character->destY = (matrizYD * map->imageSize) + map->outOfLimitsY;
		if(matrizXO > matrizXD) character->destX = (matrizXD * map->imageSize) + map->outOfLimitsX;
	
	}
	
	if(character->destX != 0 && character->destY == 0) character->destY = character->y;
	else if(character->destY != 0 && character->destX == 0) character->destX = character->x;
	
	
	if(character->destX != 0 && character->destY != 0){
	
		if(character->y < character->destY){
		
			character->y += MOVESPEED;
		
			if(character->y > character->destY) character->y = character->destY;
		
		}else if(character->x < character->destX){
		
			character->x += MOVESPEED;
		
			if(character->x > character->destX) character->x = character->destX;
		
		}else if(character->y > character->destY){
		
			character->y -= MOVESPEED;
			
			if(character->y < character->destY) character->y = character->destY;
		
		}else if(character->x > character->destX){
		
			character->x -= MOVESPEED;
		
			if(character->x < character->destX) character->x = character->destX;
		
		}
	
	}else if (character->destX == 0 && character->destY == 0){
		
		while(1){
			direction = rand() % 200;
		
			if(direction < 50) direction = 0;
			if(direction >= 50 && direction < 100) direction = 1;
			if(direction >= 100 && direction < 150) direction = 2;
			if(direction >= 150) direction = 3;
			
			correct = 0;
			
			switch(direction){
				case 0:
					for(i = 0; i < 5; i++){
						if(map->mapPptr[matrizYO][matrizXO+1] == limits[i]){
							
							character->destX = 0;
							character->destY = 0;
							correct = 0;
							break;
							
						}else{
							
							character->destX = character->x + map->imageSize;
							character->destY = character->y;
							correct = 1;
							
						}
					}
					break;
				
				case 1:
					for(i = 0; i < 5; i++){
						if(map->mapPptr[matrizYO][matrizXO-1] == limits[i]){
							
							character->destX = 0;
							character->destY = 0;
							correct = 0;
							break;
							
						}else{
							
							character->destX = character->x - map->imageSize;
							character->destY = character->y;
							correct = 1;
							
						}
					}
					break;
					
				case 2:
					for(i = 0; i < 5; i++){
						if(map->mapPptr[matrizYO+1][matrizXO] == limits[i]){
							
							character->destX = 0;
							character->destY = 0;
							correct = 0;
							break;
							
						}else{
							
							character->destX = character->x;
							character->destY = character->y + map->imageSize;
							correct = 1;
							
						}
					}
					break;
					
				case 3:
					for(i = 0; i < 5; i++){
						if(map->mapPptr[matrizYO-1][matrizXO] == limits[i]){
							
							character->destX = 0;
							character->destY = 0;
							correct = 0;
							break;
							
						}else{
							
							character->destX = character->x;
							character->destY = character->y - map->imageSize;
							correct = 1;
							
						}
					}
					break;
			}
			
			if(correct == 1) break;
		}
	}
	
	matrizXOT = ((character->x) - map->outOfLimitsX + 4) / map->imageSize;
	matrizYOT = ((character->y) - map->outOfLimitsY + 4) / map->imageSize;
	
	matrizXOU = ((character->x + (map->imageSize) - 4) - map->outOfLimitsX) / map->imageSize;
	matrizYOU = ((character->y + (map->imageSize) - 4) - map->outOfLimitsY) / map->imageSize;
	
	prematrizXOT = ((preX) - map->outOfLimitsX + 4) / map->imageSize;
	prematrizYOT = ((preY) - map->outOfLimitsY + 4) / map->imageSize;
	
	prematrizXOU = ((preX + (map->imageSize) - 4) - map->outOfLimitsX) / map->imageSize;
	prematrizYOU = ((preY + (map->imageSize) - 4) - map->outOfLimitsY) / map->imageSize;
	
	correct = 1;
	
	for(i = 0; i < 5; i++){
		
		if(map->mapPptr[matrizYOT][matrizXOT] == limits[i]){
		
			character->x = (prematrizXOU * map->imageSize) + map->outOfLimitsX;
			character->y = (prematrizYOU * map->imageSize) + map->outOfLimitsY;
			character->destX = 0;
			character->destY = 0;
			correct = 0;
		
		}
		
		if(map->mapPptr[matrizYOU][matrizXOU] == limits[i]){
			
			character->x = (prematrizXOT * map->imageSize) + map->outOfLimitsX;
			character->y = (prematrizYOT * map->imageSize) + map->outOfLimitsY;
			character->destX = 0;
			character->destY = 0;
			correct = 0;
			
		}
		
		if(map->mapPptr[matrizYOT][matrizXOU] == limits[i]){
			
			character->x = (prematrizXOT * map->imageSize) + map->outOfLimitsX;
			character->y = (prematrizYOU * map->imageSize) + map->outOfLimitsY;
			character->destX = 0;
			character->destY = 0;
			correct = 0;
			
		}
		
		if(map->mapPptr[matrizYOU][matrizXOT] == limits[i]){
			
			character->x = (prematrizXOT * map->imageSize) + map->outOfLimitsX;
			character->y = (prematrizYOU * map->imageSize) + map->outOfLimitsY;
			character->destX = 0;
			character->destY = 0;
			correct = 0;
			
		}
		
		if(correct == 0) break;
		
	}
	
	if(character->x == character->destX && character->y == character->destY){
		
		character->destX = 0;
		character->destY = 0;
		
	}
	
	printf("%.1f %.1f %d %d\n", character->x, character->destX, map->imageSize, map->outOfLimitsX);
	printf("%.1f %.1f %d %d\n", character->y, character->destY, map->imageSize, map->outOfLimitsY);
}
