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
	Ogre_t ogre[8];
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1;
	int beak = 0, x, y;
	int score = 0, missing, spawnPower = 0;
	int dragonCountDown = 0;
	int over = 0, dragonOver = 0;
	int lightning = 0;
	
	alocMap("Fase1.txt", &mapPhase1);
	
	missing = hotDogCounter(&mapPhase1);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase1);
	
	
	for (i = 0; i < 8; i++) {
		
		ogre[i].type = 'O';
		lookingForOgre(&(ogre[i]), (i+1), &mapPhase1);
		
		ogre[i].destX = 0;
		ogre[i].destY = 0;
		
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for (i = 0; i < 8; i++){
		
		lastTIME2[i] = SDL_GetTicks();
	}
	
	playSound(1);
	
	printScreen(&mapPhase1, &wizard, ogre, 8, 1, -1);
	sleep(2);
	printScreen(&mapPhase1, &wizard, ogre, 8, 1, -2);
	sleep(1);
	playSound(3);
	
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
			
			if ((finalTime + 50) % 200 == 0) {
				
				spawnLightning(&mapPhase1, &score, &missing);
				playSound(5);
			}
		
			if (finalTime % 200 == 0) {
				
				//if (dragonCountDown <= 0) dragonCountDown++;
				
			} 
			
			for (i = 0; i < 8; i++) {
				
				moveNPC(&mapPhase1, &(ogre[i]), &wizard ,&lastTIME, (mapPhase1.imageSize/4));
				
				over = gameOver(&wizard, &mapPhase1, ogre[i].x, ogre[i].y, mapPhase1.imageSize, mapPhase1.imageSize);
				
				if(over == 1) break;
			}
			
			preTime = finalTime;
		}
		
		dragonOver = dragonSpawn(&mapPhase1, &dragonCountDown, &lightning, &wizard, ogre , beak, 8);
		
		if (over == 1) exit(1);
		else if (dragonOver == 1) exit(1);
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		move(state, &wizard, &mapPhase1, &lastTIME, 150);
		eatPill(&mapPhase1, &wizard, &lightning);
		
		for (i = 0; i < 8; i++) {
						
			over = gameOver(&wizard, &mapPhase1, ogre[i].x, ogre[i].y, mapPhase1.imageSize, mapPhase1.imageSize);

			if(over == 1) break;
		}
		
		eat(&mapPhase1, &wizard, &score, &missing);
	}
}

void phase3(){
	
	Map_t mapPhase3;
	Role_t wizard;
	Ogre_t dogs[11];
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0, timeStopTime = 0;
	int beak = 0, x, y;
	int score = 0, missing, spawnPower = 0, coolDownStopTime = 0, reverseMove = 0;
	int over = 0, stop = 0;
	int remove1, remove2;
	
	alocMap("Fase3.txt", &mapPhase3);
	
	missing = hotDogCounter(&mapPhase3);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase3);
	
	
	for (i = 0; i < 11; i++) {
		
		dogs[i].type = 'O';
		lookingForOgre(&(dogs[i]), (i+1), &mapPhase3);
		
		dogs[i].destX = 0;
		dogs[i].destY = 0;
		
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for (i = 0; i < 8; i++){
		
		lastTIME2[i] = SDL_GetTicks();
	}
	
	playSound(1);
	
	printScreen(&mapPhase3, &wizard, dogs, 11, 3, -1);
	sleep(2);
	printScreen(&mapPhase3, &wizard, dogs, 11, 3, -2);
	sleep(1);
	playSound(3);
	
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
			
			if (stop != 1){
				for (i = 0; i < 11; i++) {
				
					moveNPC(&mapPhase3, &(dogs[i]), &wizard ,&lastTIME, (mapPhase3.imageSize/1.5));
				
					over = gameOver(&wizard, &mapPhase3, dogs[i].x, dogs[i].y, mapPhase3.imageSize, mapPhase3.imageSize);
				
					if(over == 1) break;
				}
			} 
		
			
			preTime = finalTime;
		}
		
		printScreen(&mapPhase3, &wizard, dogs, 11, 3, beak);
		
		if (over == 1) exit(1);
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if(timeStopTime != 0)move(state, &wizard, &mapPhase3, &lastTIME, 75);
		else if(reverseMove == 0) move(state, &wizard, &mapPhase3, &lastTIME, 150);
		else reverseMoves(state, &wizard, &mapPhase3, &lastTIME, 150);
		
		
		if (stop != 1){
			for (i = 0; i < 11; i++) {
						
				over = gameOver(&wizard, &mapPhase3, dogs[i].x, dogs[i].y, mapPhase3.imageSize, mapPhase3.imageSize);

				if(over == 1) break;
			}
		}
		
		
		eat(&mapPhase3, &wizard, &score, &missing);
		
		if (state[SDL_SCANCODE_F] && coolDownStopTime == 0){
			
			stopTimeMode();
			
			playSound(6);
			
			stop = 1;
		
			timeStopTime = finalTime;
		
		}
		
		if(finalTime >= (timeStopTime + 70) && timeStopTime != 0){
			
			makeTextures();
			
			stop = 0;
			
			timeStopTime = 0;
			
			coolDownStopTime = finalTime;
			
			reverseMove = finalTime;
		}
		
		if(finalTime == (reverseMove + 150) && reverseMove != 0) reverseMove = 0;
		if(finalTime >= (coolDownStopTime + 300) && coolDownStopTime != 0) coolDownStopTime = 0;
	}
	
}
