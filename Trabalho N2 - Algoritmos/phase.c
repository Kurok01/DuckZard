#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "interface.h"
#include "mapFunctions.h"
#include "structs.h"
#include "actions.h"

void phase1 () {
	
	Map_t mapPhase1;
	Role_t wizard;
	Role_t ogre[8];
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0;
	int beak = 0, x, y, xD, yD;
	int score = 0, missing;
	int dragonCountDown = 0;
	
	alocMap("Fase1.txt", &mapPhase1);
	
	missing = hotDogCounter(&mapPhase1);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase1);
	
	
	for (i = 0; i < 8; i++) {
		
		ogre[i].type = 'O';
		lookingFor(&(ogre[i]), (i+1), &mapPhase1);
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for(i = 0; i < 8; i++){
		
		lastTIME2[i] = SDL_GetTicks();
		
	}
				
	while (missing != 0) {
		
		srand(time(0));
		
		secondTime = clock();
		aux = secondTime - firstTime;
		aux /= CLOCKS_PER_SEC;
		finalTime = aux * 10;
	
		if (finalTime > preTime) {
			
			if (finalTime % 2 == 0) {
				
				if (beak == 1) beak = 0;
				else beak = 1;
			}
		
			if (finalTime % 100 == 0) {
				
				if (dragonCountDown == 0) dragonCountDown++;
			} 
			
			xD = (wizard.x - mapPhase1.outOfLimitsX) / mapPhase1.imageSize;
			yD = (wizard.y - mapPhase1.outOfLimitsY) / mapPhase1.imageSize;
				
			for (i = 0; i < 8; i++) {
				
				x = (ogre[i].x - mapPhase1.outOfLimitsX) / mapPhase1.imageSize;
				y = (ogre[i].y - mapPhase1.outOfLimitsY) / mapPhase1.imageSize;
				
				if(x == xD){
					
					if(ogre[i].y < wizard.y) ogre[i].direction = 2;
					else ogre[i].direction = 3;
					
				}else if(y == yD){
					
					if(ogre[i].x < wizard.x) ogre[i].direction = 0;
					else ogre[i].direction = 1;
					
				}else{
					
					ogre[i].direction = rand()%4;
					
				}
				
			}
			
			preTime = finalTime;
		}
		
		printScreen(&mapPhase1, &wizard, ogre, 8, 1, beak, &dragonCountDown);
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		move(state, &wizard, &mapPhase1, &lastTIME);
		
		for(i = 0; i < 8; i++){
			
			moveNPC(&mapPhase1, &(ogre[i]), &(lastTIME2[i]));
		}
		
		eat(&mapPhase1, &wizard, &score, &missing);
	}
}
