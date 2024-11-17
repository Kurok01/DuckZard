#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void moveNPC(Map_t *map, Ogre_t *character, Uint32 *lastTIME) {

	float speedX, speedY;
	float preX = character->x, preY = character->y;
	int middleX, middleY, x, y, direction;
	int i, correct = 0;
	char limits[] = "*$";
	
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - *lastTIME) / 1000.00;
	
	if(character->destX != 0 && character->destY != 0){
		
		if(character->x != character->destX){
			
			if(character->x < character->destX){
				
				character->x += 10;
				
				if(character->x > character->destX){
					
					character->x = character->destX;
					
				} 
				
			}
			else{
				
				character->x -= 10;
				
				if(character->x < character->destX){
					
					character->x = character->destX;
					
				}
			} 

		}else if(character->y != character->destY){
			
			if(character->y < character->destY){
				
				character->y += 10;
				
				if(character->y > character->destY){
					
					character->y = character->destY;
					
				} 
				
			}
			else{
				character->y -= 10;
				
				if(character->y < character->destY){
					
					character->y = character->destY;
					
				}	
				
			}
			
		}else{
			
			character->destX = 0;
			character->destY = 0;
			
		}
		
	}else{
		
		while (correct == 0) {
	
		middleX = character->x;
		middleY = character->y;
		
		x = (middleX - map->outOfLimitsX) / map->imageSize;
		y = (middleY - map->outOfLimitsY) / map->imageSize;
		
		direction = rand() % 4;
		
		switch(direction){
			case 0:
				if(map->mapPptr[y][x+1] == ' '){
					correct = 1;
					
					for(i = 0; i < 5; i++){
						
						if(map->mapPptr[y][x+1+i] == ' ') correct = 0;
						else{
							correct = 1;
							character->destX = ((i) * map->imageSize) +  middleX;
							character->destY = middleY;
							break;
						}  
					}
					
					if(correct == 0){
						correct = 1;
						character->destX = ((5) * map->imageSize) + middleX;
						character->destY = middleY;
						break;
						
					}else{
						break;
					}
				
					
				}
				else correct = 0;
				break;
			case 1:
				if(map->mapPptr[y][x-1] == ' '){
					correct = 1;
					
					for(i = 0; i < 5; i++){
						
						if(map->mapPptr[y][x-1-i] == ' ') correct = 0;
						else{
							correct = 1;
							character->destX = middleX - ((i) * map->imageSize);
							character->destY = middleY;
							break;
						}  
					}
					
					if(correct == 0){
						correct = 1;
						character->destX = middleX - ((5) * map->imageSize);
						character->destY = middleY;
						break;
						
					}else{
						break;
					}
				}
				else correct = 0;
				break;
			case 2:
				if(map->mapPptr[y+1][x] == ' '){
					correct = 1;
					
					for(i = 0; i < 5; i++){
						
						if(map->mapPptr[y+1+i][x] == ' ') correct = 0;
						else{
							correct = 1;
							character->destX = middleX;
							character->destY = middleY + ((i) * map->imageSize);
							break;
						}  
					}
					
					if(correct == 0){
						correct = 1;
						character->destX = middleX;
						character->destY = middleY + ((5) * map->imageSize);
						break;
						
					}else{
						break;
					}
				}
				else correct = 0;
				break;
			case 3:
				if(map->mapPptr[y-1][x] == ' '){
					correct = 1;
					
					for(i = 0; i < 5; i++){
						
						if(map->mapPptr[y-1-i][x] == ' ') correct = 0;
						else{
							correct = 1;
							character->destX = middleX;
							character->destY = middleY - ((i) * map->imageSize);
							break;
						}  
					}
					
					if(correct == 0){
						correct = 1;
						character->destX = middleX;
						character->destY = middleY - ((5) * map->imageSize);
						break;
						
					}else{
						break;
					}
				}
				else correct = 0;
			}
		
		}
		
	}
	
	*lastTIME = currentTime;
}
