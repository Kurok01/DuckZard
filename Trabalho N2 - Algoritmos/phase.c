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
	Wizard_t wizard;
	Monster_t ogres[8];
	int print, selection = 1;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1, pauseTime;
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
		
		ogres[i].type = 'O';
		lookingForMonster (&(ogres[i]), (i+1), &mapPhase1);
		
		ogres[i].destX = 0;
		ogres[i].destY = 0;
		
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for (i = 0; i < 8; i++){
		
		lastTIME2[i] = SDL_GetTicks();
	}
	
	playSound(1);
	
	printScreen(&mapPhase1, &wizard, ogres, 8, 1, -1);
	sleep(2);
	printScreen(&mapPhase1, &wizard, ogres, 8, 1, -2);
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
			
			if ((finalTime + 150) % 400 == 0) {
				
				spawnLightning(&mapPhase1, &score, &missing);
				playSound(5);
			}
		
			if (finalTime % 400 == 0) {
				
				if (dragonCountDown <= 0) dragonCountDown++;
				
			} 
			
			for (i = 0; i < 8; i++) {
				
				moveNPC(&mapPhase1, &(ogres[i]), &wizard ,&lastTIME, (mapPhase1.imageSize/4));
				
				over = gameOver(&wizard, &mapPhase1, ogres[i].x, ogres[i].y, mapPhase1.imageSize, mapPhase1.imageSize);
				
				if(over == 1) break;
			}
			
			preTime = finalTime;
		}
		
		dragonOver = phase1ElementsSpawn(&mapPhase1, &dragonCountDown, &lightning, &wizard, ogres, beak, 8);
		
		if (over == 1) exit(1);
		else if (dragonOver == 1) exit(1);
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_ESCAPE]){
            while(1){
                if(print == 0) pauseScreen(selection);
                else pauseScreen(4);

                if(finalTime > (pauseTime + 4)){
                    pauseTime = finalTime;

                    if(print == 0) print = 1;
                    else print = 0;
                }

                while(SDL_PollEvent(&event));

                state = SDL_GetKeyboardState(NULL);

                if(state[SDL_SCANCODE_W]){
                    if(selection > 1) selection--;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_S]){
                    if(selection < 3) selection++;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 1){
                    break;
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 3){
                    exit(1);
                }
            }
        }

		move(state, &wizard, &mapPhase1, &lastTIME, 150);
		eatPill(&mapPhase1, &wizard, &lightning);
		
		for (i = 0; i < 8; i++) {
						
			over = gameOver(&wizard, &mapPhase1, ogres[i].x, ogres[i].y, mapPhase1.imageSize, mapPhase1.imageSize);

			if(over == 1) break;
		}
		
		eat(&mapPhase1, &wizard, &score, &missing);
	}
}

void phase2 () {
	
	Map_t mapPhase2;
	Wizard_t wizard;
	Monster_t yetis[8], snowBall[40];
	int print, selection = 1, numSnowBall = 0;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1, pauseTime;
	int beak = 0, x, y;
	int score = 0, missing;
	int over = 0;
	int blizzard = 0, coolDownFireTime = 0, fireDuration = 0;
	
	alocMap("Fase2.txt", &mapPhase2);
	
	missing = hotDogCounter(&mapPhase2);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase2);
	
	
	for (i = 0; i < 8; i++) {
		
		yetis[i].type = 'O';
		lookingForMonster (&(yetis[i]), (i+1), &mapPhase2);
		
		yetis[i].destX = 0;
		yetis[i].destY = 0;
		
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for (i = 0; i < 8; i++){
		
		lastTIME2[i] = SDL_GetTicks();
	}
	
	playSound(1);
	
	printScreen(&mapPhase2, &wizard, yetis, 8, 2, -1);
	sleep(2);
	printScreen(&mapPhase2, &wizard, yetis, 8, 2, -2);
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
			
			if (finalTime % 400 == 0 && blizzard == 0) {
				
				blizzard = 1;
				playSound(6);
				freeze(&mapPhase2, blizzard);
			}
			
			
			if (finalTime % 800 == 0 && blizzard >= 1) blizzard = 0;
			
			for (i = 0; i < 8; i++) {
				
				moveNPC(&mapPhase2, &(yetis[i]), &wizard ,&lastTIME, (mapPhase2.imageSize/4));
				
				over = gameOver(&wizard, &mapPhase2, yetis[i].x, yetis[i].y, mapPhase2.imageSize, mapPhase2.imageSize);
				
				if(over == 1) exit(1);
			}
			
			if(finalTime % 5 == 0 && blizzard == 0){
				
				if(finalTime % 40 == 0) playSound(8);
				spawnSnowBall(&mapPhase2, snowBall, &numSnowBall);
				
			}
			
			if(blizzard == 1 && numSnowBall != 0){
				
				numSnowBall = 0;
			}
			
			for (i = 0; i < numSnowBall; i++) {
				
				if(i == 0) moveSnowBall(&mapPhase2, snowBall, &numSnowBall);

				over = gameOver(&wizard, &mapPhase2, snowBall[i].x, snowBall[i].y, mapPhase2.imageSize, mapPhase2.imageSize);
				
				if(over == 1) exit(1);
			}
			
			preTime = finalTime;
		}
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
		}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_ESCAPE]){
            while(1){
                if(print == 0) pauseScreen(selection);
                else pauseScreen(4);

                if(finalTime > (pauseTime + 4)){
                    pauseTime = finalTime;

                    if(print == 0) print = 1;
                    else print = 0;
                }

                while(SDL_PollEvent(&event));

                state = SDL_GetKeyboardState(NULL);

                if(state[SDL_SCANCODE_W]){
                    if(selection > 1) selection--;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_S]){
                    if(selection < 3) selection++;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 1){
                    break;
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 3){
                    exit(1);
                }
            }
        }
		
		phase2ElementsSpawn(&mapPhase2, &blizzard, &wizard, yetis, beak, 8);
		
		if (blizzard >= 1) {
			
			move(state, &wizard, &mapPhase2, &lastTIME, 100);	
		}
		
		move(state, &wizard, &mapPhase2, &lastTIME, 150);
		
		if (state[SDL_SCANCODE_F] && coolDownFireTime == 0) {
			
			playSound(7);
			fireDuration = finalTime;
			spawnFire(&mapPhase2, wizard.direction, wizard.x, wizard.y);
			deFreeze(&mapPhase2, &wizard, fireDuration, finalTime);
			coolDownFireTime = finalTime;
		}
		
		if (finalTime <= (fireDuration + 50) && fireDuration != 0) {
			
			spawnFire(&mapPhase2, wizard.direction, wizard.x, wizard.y);
			deFreeze(&mapPhase2, &wizard, fireDuration, finalTime);
			
		} else {
			
			spawnFire(&mapPhase2, wizard.direction, -100, -100);
			fireDuration = 0;
		}
		
		if (finalTime >= (coolDownFireTime + 70) && (coolDownFireTime) != 0) {
			
			coolDownFireTime = 0;
		}
		
		for (i = 0; i < 8; i++) {
						
			over = gameOver(&wizard, &mapPhase2, yetis[i].x, yetis[i].y, mapPhase2.imageSize, mapPhase2.imageSize);

			if(over == 1) exit(1);
		}
		
		eat(&mapPhase2, &wizard, &score, &missing);
	}
}

void phase3(){
	
	Map_t mapPhase3;
	Wizard_t wizard;
	Monster_t dogs[11];
	int print, selection = 1;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0, timeStopTime = 0, pauseTime;
	int beak = 0, x, y;
	int score = 0, missing, spawnPower = 0, coolDownStopTime = 0, reverseMove = 0;
	int over = 0, stop = 0;

	
	alocMap("Fase3.txt", &mapPhase3);
	
	missing = hotDogCounter(&mapPhase3);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase3);
	
	
	for (i = 0; i < 11; i++) {
		
		dogs[i].type = 'O';
		lookingForMonster(&(dogs[i]), (i+1), &mapPhase3);
		
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
		
		if(state[SDL_SCANCODE_ESCAPE]){
            while(1){
                if(print == 0) pauseScreen(selection);
                else pauseScreen(4);

                if(finalTime > (pauseTime + 4)){
                    pauseTime = finalTime;

                    if(print == 0) print = 1;
                    else print = 0;
                }

                while(SDL_PollEvent(&event));

                state = SDL_GetKeyboardState(NULL);

                if(state[SDL_SCANCODE_W]){
                    if(selection > 1) selection--;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_S]){
                    if(selection < 3) selection++;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 1){
                    break;
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 3){
                    exit(1);
                }
            }
        }
		
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

void phase4(){
	
	Map_t mapPhase4;
	Wizard_t wizard;
	Monster_t clone[40];
	int print, selection = 1, numClones = 4;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0, pauseTime, transformationCoolDown = 0, transformationDuration = 0;
	int beak = 0, x, y;
	int score = 0, missing;
	int over = 0, stop = 0;

	
	alocMap("Fase4.txt", &mapPhase4);
	
	missing = hotDogCounter(&mapPhase4);
	
	wizard.type = 'D';
	
	lookingFor(&wizard, 1, &mapPhase4);
	
	
	for (i = 0; i < 4; i++) {
		
		clone[i].type = 'O';
		lookingForMonster(&(clone[i]), (i+1), &mapPhase4);
		
		clone[i].destX = 0;
		clone[i].destY = 0;
		
	}
	
	firstTime = clock(); 
	
	wizard.direction = 2;
	
	Uint32 lastTIME, lastTIME2[8];
	
	lastTIME = SDL_GetTicks();
	
	for (i = 0; i < 4; i++){
		
		lastTIME2[i] = SDL_GetTicks();
	}
	
	playSound(1);
	
	printScreen(&mapPhase4, &wizard, clone, 4, 4, -1);
	sleep(2);
	printScreen(&mapPhase4, &wizard, clone, 4, 4, -2);
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
				for (i = 0; i < numClones; i++) {
				
					moveNPC(&mapPhase4, &(clone[i]), &wizard ,&lastTIME, (mapPhase4.imageSize/4));
				
					if(wizard.type == 'D')over = gameOver(&wizard, &mapPhase4, clone[i].x, clone[i].y, mapPhase4.imageSize, mapPhase4.imageSize);
				
					if(over == 1) break;
				}
			}
			
			if(finalTime % 300 == 0){
				
				spawnClone(&mapPhase4, clone, &numClones);
				
			}
			
			preTime = finalTime;
		}
		
		printScreen(&mapPhase4, &wizard, clone, numClones, 4, beak);
		
		if (over == 1) exit(1);
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_F] && transformationCoolDown == 0){
			
			wizard.type = 'O';
			transformationDuration = finalTime;
			
		}
		
		if(finalTime >= (transformationDuration + 100) && transformationDuration != 0){
			
			wizard.type = 'D';
			transformationCoolDown = finalTime;
			transformationDuration = 0;
			
		}
		
		if(finalTime >= (transformationCoolDown + 100) && transformationCoolDown != 0){
			
			transformationCoolDown = 0;
			
		}
		
		if(state[SDL_SCANCODE_ESCAPE]){
            while(1){
                if(print == 0) pauseScreen(selection);
                else pauseScreen(4);

                if(finalTime > (pauseTime + 4)){
                    pauseTime = finalTime;

                    if(print == 0) print = 1;
                    else print = 0;
                }

                while(SDL_PollEvent(&event));

                state = SDL_GetKeyboardState(NULL);

                if(state[SDL_SCANCODE_W]){
                    if(selection > 1) selection--;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_S]){
                    if(selection < 3) selection++;
                    pauseScreen(selection);
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 1){
                    break;
                }

                if(state[SDL_SCANCODE_RETURN] && selection == 3){
                    exit(1);
                }
            }
        }
        
        move(state, &wizard, &mapPhase4, &lastTIME, 150);
		
		if (stop != 1){
			for (i = 0; i < numClones; i++) {
						
				if(wizard.type == 'D') over = gameOver(&wizard, &mapPhase4, clone[i].x, clone[i].y, mapPhase4.imageSize, mapPhase4.imageSize);

				if(over == 1) break;
			}
		}
		
		
		eat(&mapPhase4, &wizard, &score, &missing);
	}
	
}
