#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "interface.h"
#include "mapFunctions.h"
#include "structs.h"
#include "actions.h"
#include "statistics.h"

int phase1 () {
	
	Map_t mapPhase1;
	Wizard_t wizard;
	Monster_t ogres[8];
	int print, selection = 1;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1, pauseTime, shieldTime = 0;
	int beak = 0, x, y;
	int score = 0, missing, spawnPower = 0;
	int dragonCountDown = 0;
	int over = 3, dragonOver = 0, preOver, shield = 0;
	int lightning = 0, option;
	
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
	
	printScreen(&mapPhase1, &wizard, ogres, 8, 1, -1, shield);
	sleep(2);
	printScreen(&mapPhase1, &wizard, ogres, 8, 1, -2, shield);
	sleep(1);
	playSound(7);
	
	playSound(1);
	
	while (missing != 0) {
			
		preOver = over;
		
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
				playSound(9);
			}
		
			if (finalTime % 400 == 0) {
				
				if (dragonCountDown <= 0) dragonCountDown++;
				
			}
			
			if(shieldTime == 0 && shield == 1){
				
				shieldTime = finalTime;
				
			}
			
			if(finalTime > (shieldTime + 70) && shieldTime != 0){
				
				shield = 0;
				shieldTime = 0;
			}
			
			for (i = 0; i < 8; i++) {
				
				moveNPC(&mapPhase1, &(ogres[i]), &wizard ,&lastTIME, (mapPhase1.imageSize/4));
	
				if(shield != 1) over -= gameOver(&wizard, &mapPhase1, ogres[i].x, ogres[i].y, mapPhase1.imageSize, mapPhase1.imageSize);
				
				if(preOver != over) shield = 1;
			}
			
			preTime = finalTime;
		}
		
		if(shield != 1) over -= phase1ElementsSpawn(&mapPhase1, &dragonCountDown, &lightning, &wizard, ogres, beak, 8, 1, shield);
		else phase1ElementsSpawn(&mapPhase1, &dragonCountDown, &lightning, &wizard, ogres, beak, 8, 1, shield);
		
		if(preOver != over) shield = 1;
		
		if (over <= 0) break;
		
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
                    return 0;
                }
            }
        }

		move(state, &wizard, &mapPhase1, &lastTIME, 150);
		eatPill(&mapPhase1, &wizard, &lightning);
		
		for (i = 0; i < 8; i++) {

			if(shield != 1) over -= gameOver(&wizard, &mapPhase1, ogres[i].x, ogres[i].y, mapPhase1.imageSize, mapPhase1.imageSize);
			
			if(preOver != over) shield = 1;
		}
		
		eat(&mapPhase1, &wizard, &score, &missing);
	}
	
	saveData(over, finalTime, 1);
	changeStaticsMap();
	
	freeMap(&mapPhase1);
	
	if(missing == 0){
		option = winningScreen();
		if(option == 0){
			printScreen(&mapPhase1, &wizard, ogres, 8, 0, beak, shield);
			return 0;
		}else{
			return 1;
		}	
	}else{
		
		option = gameOverScreen();
		
		if(option == 0){
			printScreen(&mapPhase1, &wizard, ogres, 8, 0, beak, shield);
			return -1;
		}else{
			return 0;
		}	
		
		
	}
}

int phase2 () {
	
	Map_t mapPhase2;
	Wizard_t wizard;
	Monster_t yetis[8], snowBall[40];
	int print, selection = 1, numSnowBall = 0;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1, pauseTime;
	int beak = 0, x, y;
	int score = 0, missing;
	int over = 3, preOver, shield = 0, option;
	int blizzard = 0, coolDownFireTime = 0, fireDuration = 0, shieldTime = 0;
	
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
	
	printScreen(&mapPhase2, &wizard, yetis, 8, 2, -1, shield);
	sleep(2);
	printScreen(&mapPhase2, &wizard, yetis, 8, 2, -2, shield);
	sleep(1);
	playSound(7);
	
	playSound(2);
	
	while (missing != 0) {
		
		preOver = over;
			
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
				playSound(10);
				freeze(&mapPhase2, blizzard);
			}
			
			
			if (finalTime % 800 == 0 && blizzard >= 1) blizzard = 0;
			
			for (i = 0; i < 8; i++) {
				
				moveNPC(&mapPhase2, &(yetis[i]), &wizard ,&lastTIME, (mapPhase2.imageSize/4));
				
				if(shield != 1) over -= gameOver(&wizard, &mapPhase2, yetis[i].x, yetis[i].y, mapPhase2.imageSize, mapPhase2.imageSize);
				
				if(preOver != over) shield = 1;
			}
			
			if(finalTime % 5 == 0 && blizzard == 0){
				
				if(finalTime % 40 == 0) playSound(8);
				spawnSnowBall(&mapPhase2, snowBall, &numSnowBall);
				
			}
			
			if(blizzard == 1 && numSnowBall != 0){
				
				numSnowBall = 0;
			}
			
			if(shieldTime == 0 && shield == 1){
				
				shieldTime = finalTime;
				
			}
			
			if(finalTime > (shieldTime + 70) && shieldTime != 0){
				
				shield = 0;
				shieldTime = 0;
			}
			
			for (i = 0; i < numSnowBall; i++) {
				
				if(i == 0) moveSnowBall(&mapPhase2, snowBall, &numSnowBall);

				if(shield != 1) over -= gameOver(&wizard, &mapPhase2, snowBall[i].x, snowBall[i].y, mapPhase2.imageSize, mapPhase2.imageSize);
				
				if(preOver != over) shield = 1;
			}
			
			preTime = finalTime;
		}
		
		if(over <= 0) break;
		
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
                	
                	resetSnowBall();
                    return 0;
                }
            }
        }
		
		phase2ElementsSpawn(&mapPhase2, &blizzard, &wizard, yetis, beak, 8, 2, shield);
		
		if (blizzard >= 1) {
			
			move(state, &wizard, &mapPhase2, &lastTIME, 100);	
		}
		
		move(state, &wizard, &mapPhase2, &lastTIME, 150);
		
		if (state[SDL_SCANCODE_F] && coolDownFireTime == 0) {
			
			playSound(11);
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
						
			if(shield != 1) over -= gameOver(&wizard, &mapPhase2, yetis[i].x, yetis[i].y, mapPhase2.imageSize, mapPhase2.imageSize);

			if(preOver != over) shield = 1;
		}
		
		eat(&mapPhase2, &wizard, &score, &missing);
	}
	
	saveData(over, finalTime, 1);
	changeStaticsMap();
	
	freeMap(&mapPhase2);
	
	resetSnowBall();
	
	if(missing == 0){
		
		option = winningScreen();
		if(option == 0){
			printScreen(&mapPhase2, &wizard, yetis, 8, 0, beak, shield);
			return 0;
		}else{
			return 1;
		}
	}else{
		
		option = gameOverScreen();
		if(option == 0){
			printScreen(&mapPhase2, &wizard, yetis, 8, 0, beak, shield);
			return -1;
		}else{
			return 0;
		}	
	}
	
}

int phase3(){
	
	Map_t mapPhase3;
	Wizard_t wizard;
	Monster_t dogs[11];
	int print, selection = 1;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0, timeStopTime = 0, pauseTime;
	int beak = 0, x, y, shield = 0;
	int score = 0, missing, spawnPower = 0, coolDownStopTime = 0, reverseMove = 0, shieldTime = 0;
	int over = 3, stop = 0, preOver, option;

	
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
	
	printScreen(&mapPhase3, &wizard, dogs, 11, 3, -1, shield);
	sleep(2);
	printScreen(&mapPhase3, &wizard, dogs, 11, 3, -2, shield);
	sleep(1);
	playSound(7);
	
	playSound(3);
	
	while (missing != 0) {
		
		preOver = over;
		
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
				
					if(shield != 1) over -= gameOver(&wizard, &mapPhase3, dogs[i].x, dogs[i].y, mapPhase3.imageSize, mapPhase3.imageSize);
				
					if(preOver != over) shield = 1;
				}
			}
			
			if(shieldTime == 0 && shield == 1){
				
				shieldTime = finalTime;
				
			}
			
			if(finalTime > (shieldTime + 70) && shieldTime != 0){
				
				shield = 0;
				shieldTime = 0;
			}
		
			
			preTime = finalTime;
		}
		
		printScreen(&mapPhase3, &wizard, dogs, 11, 3, beak, shield);
		
		if (over <= 0) break;
		
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
                    return 0;
                }
            }
        }
		
		if(timeStopTime != 0)move(state, &wizard, &mapPhase3, &lastTIME, 75);
		else if(reverseMove == 0) move(state, &wizard, &mapPhase3, &lastTIME, 150);
		else reverseMoves(state, &wizard, &mapPhase3, &lastTIME, 150);
		
		
		if (stop != 1){
			for (i = 0; i < 11; i++) {
						
				if(shield != 1) over -= gameOver(&wizard, &mapPhase3, dogs[i].x, dogs[i].y, mapPhase3.imageSize, mapPhase3.imageSize);

				if(preOver != over) shield = 1;
			}
		}
		
		
		eat(&mapPhase3, &wizard, &score, &missing);
		
		if (state[SDL_SCANCODE_E] && coolDownStopTime == 0){
			
			stopTimeMode();
			
			playSound(13);
			
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
	
	saveData(over, finalTime, 1);
	changeStaticsMap();
	
	freeMap(&mapPhase3);
	
	if(missing == 0){
		option = winningScreen();
		if(option == 0){
			printScreen(&mapPhase3, &wizard, dogs, 11, 0, beak, shield);
			return 0;
		}else{
			return 1;
		}
	}else{
		
		option = gameOverScreen();
		if(option == 0){
			printScreen(&mapPhase3, &wizard, dogs, 11, 0, beak, shield);
			return -1;
		}else{
			return 0;
		}	
	}
}

int phase4(){
	
	Map_t mapPhase4;
	Wizard_t wizard;
	Monster_t clone[40];
	int print, selection = 1, numClones = 4;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 0, pauseTime, transformationCoolDown = 0, transformationDuration = 0, shieldTime = 0;
	int beak = 0, x, y, shield = 0;
	int score = 0, missing;
	int over = 3, preOver, stop = 0, option;

	
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
	
	printScreen(&mapPhase4, &wizard, clone, 4, 4, -1, shield);
	sleep(2);
	printScreen(&mapPhase4, &wizard, clone, 4, 4, -2, shield);
	sleep(1);
	playSound(7);
	
	playSound(0);
	while (missing != 0) {
		
		preOver = over;
		
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
			
			for (i = 0; i < numClones; i++) {
				
				moveNPC(&mapPhase4, &(clone[i]), &wizard ,&lastTIME, (mapPhase4.imageSize/4));
				
				if(wizard.type == 'D' && shield != 1) over -= gameOver(&wizard, &mapPhase4, clone[i].x, clone[i].y, mapPhase4.imageSize, mapPhase4.imageSize);
				
				if(preOver != over) shield = 1;
			}
			
			if(shieldTime == 0 && shield == 1){
				
				shieldTime = finalTime;
				
			}
			
			if(finalTime > (shieldTime + 70) && shieldTime != 0){
				
				shield = 0;
				shieldTime = 0;
			}
			
			if(finalTime % 300 == 0){
				
				spawnClone(&mapPhase4, clone, &numClones, 4);	
			}
			
			preTime = finalTime;
		}
		
		printScreen(&mapPhase4, &wizard, clone, numClones, 4, beak, shield);
		
		if (over <= 0) break;
		
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
                    return 0;
                }
            }
        }
        
        move(state, &wizard, &mapPhase4, &lastTIME, 150);
		
		if (stop != 1){
			for (i = 0; i < numClones; i++) {
						
				if(wizard.type == 'D' && shield != 1) over -= gameOver(&wizard, &mapPhase4, clone[i].x, clone[i].y, mapPhase4.imageSize, mapPhase4.imageSize);

				if(preOver != over) shield = 1;
			}
		}
		
		
		eat(&mapPhase4, &wizard, &score, &missing);
	}
	
	saveData(over, finalTime, 1);
	changeStaticsMap();
	
	freeMap(&mapPhase4);
	
	if(missing == 0){
		option = winningScreen();
		if(option == 0){
			printScreen(&mapPhase4, &wizard, clone, numClones, 0, beak, shield);
			return 0;
		}else{
			return 1;
		}
	}else{
		
		option = gameOverScreen();
		if(option == 0){
			printScreen(&mapPhase4, &wizard, clone, numClones, 0, beak, shield);
			return -1;
		}else{
			return 0;
		}	
	}
	
}

int finalPhase () {
	
	Map_t mapPhase5;
	Wizard_t wizard;
	Monster_t monsters[16];
	int print, selection = 1, numClones = 8;
	int coordenates = 0, i;
	float firstTime, secondTime, aux = 0;
	int finalTime, preTime = 1, pauseTime, timeStopTime = 0, transformationCoolDown = 0, transformationDuration = 0;
	int beak = 0, x, y;
	int score = 0, missing = 4, spawnPower = 0, coolDownStopTime = 0, reverseMove = 0;
	int dragonCountDown = 0;
	int over = 3, preOver, dragonOver = 0, coolDownFireTime = 0, fireDuration = 0, stop = 0, deFreezeCorrect = 0;
	int lightning = 0, shield = 0;
	int auxTime = 0, shieldTime = 0, option;
	int blizzard = 0;
	int which[4] = {4, 4, 4, 4};
	
	alocMap("Fase5.txt", &mapPhase5);
	
	wizard.type = 'D';
	
	lookingFor (&wizard, 1, &mapPhase5);
	
	for (i = 0; i < 8; i++) {
		
		monsters[i].type = 'O';
		
		lookingForMonster(&monsters[i], i+1, &mapPhase5);
		
		monsters[i].destX = 0;
		monsters[i].destY = 0;
	}
	
	firstTime = clock();
	
	wizard.direction = 0;
	
	Uint32 lastTIME;
	
	lastTIME = SDL_GetTicks();
	
	printScreen(&mapPhase5, &wizard, monsters, 8, 5, -1, shield);
	
	spawnNexus(&mapPhase5, which);
	
	printScreen(&mapPhase5, &wizard, monsters, 8, 5, -1, shield);
	sleep(2);
	printScreen(&mapPhase5, &wizard, monsters, 8, 5, -2, shield);
	sleep(1);
	playSound(7);
	
	playSound(0);
	
	while (missing != 0) {
		
		preOver = over;
		
		srand(time(0));
		
		secondTime = clock();
		
		aux = secondTime - firstTime;
		
		aux /= CLOCKS_PER_SEC;
			
		if (timeStopTime == 0) {
		
			finalTime = (aux * 10) - auxTime;
			
			if (auxTime != 0) auxTime = 0;
		
		} else {
			
			auxTime = (aux * 10) - finalTime;
		}
		
		if (finalTime > preTime) {
				
			if (finalTime % 2) {
				
				if (beak == 1) beak = 0;
				else beak = 1; 
			}
			
			if ((finalTime + 150) % 400 == 0 && which[0] > 0) {
				
				spawnLightning(&mapPhase5, &score, &missing);
				playSound(9);
			}
		
			if (finalTime % 400 == 0 && which[0] > 0) {
				
				if (dragonCountDown <= 0) dragonCountDown++;
				
			}
			
			if (finalTime % 400 == 0 && blizzard == 0 && timeStopTime == 0 && which[1] > 0) {
				
				blizzard = 1;
				playSound(10);
			}
			
			if(finalTime % 300 == 0 && timeStopTime == 0 && which[3] > 0){
				
				spawnClone(&mapPhase5, monsters, &numClones, 5);	
			}
			
			if (finalTime % 600 == 0 && blizzard >= 1 && timeStopTime == 0) blizzard = 0; 
				
			if(shieldTime == 0 && shield == 1){
				
				shieldTime = finalTime;
				
			}
			
			if(finalTime > (shieldTime + 70) && shieldTime != 0){
				
				shield = 0;
				shieldTime = 0;
			}
			
			for (i = 0; i < numClones; i++) {
				
				if(which[0] == 0 && (i <= 1)) continue; 
				if(which[1] == 0 && (i == 2 || i == 3)) continue; 
				if(which[2] == 0 && (i == 4 || i == 5)) continue; 
				if(which[3] == 0 && (i == 6 || i >= 7)) continue; 
				
				moveNPC(&mapPhase5, &(monsters[i]), &wizard ,&lastTIME, (mapPhase5.imageSize/4));
				
				if(shield != 1) over -= gameOver(&wizard, &mapPhase5, monsters[i].x, monsters[i].y, mapPhase5.imageSize, mapPhase5.imageSize);
				
				if(preOver != over) shield = 1;
			}
				
			preTime = finalTime;			
		}
			
			if(which[0] == 0){
				
				monsters[0].x = -100;
				monsters[1].y = -100;
				
			}
			if(which[1] == 0){
				
				monsters[2].x = -100;
				monsters[3].y = -100;
				
			}
			if(which[2] == 0){
				
				monsters[4].x = -100;
				monsters[5].y = -100;
				
			}
			if(which[3] == 0){
				
				for(i = 6; i <= 15; i++){
					
					monsters[i].x = -100;
				}
				
			}
			
			if (timeStopTime == 0) phase2ElementsSpawn(&mapPhase5, &blizzard, &wizard, monsters, beak, numClones, 5, shield);
			
			if (timeStopTime == 0 && shield != 1) over -= phase1ElementsSpawn(&mapPhase5, &dragonCountDown, &lightning, &wizard, monsters, beak, numClones, 5, shield);
			else if(timeStopTime == 0 && shield == 1) phase1ElementsSpawn(&mapPhase5, &dragonCountDown, &lightning, &wizard, monsters, beak, numClones, 5, shield);
			else printScreen(&mapPhase5, &wizard, monsters, numClones, 5, beak, shield);
				
		if(over <= 0) break;
		
		SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT);
	}
	
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_C] && transformationCoolDown == 0 && which[3] > 0){
			
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
                    return 0;
                }  
            }
        }
        
        if (blizzard >= 1) {
			
			move(state, &wizard, &mapPhase5, &lastTIME, 100);	
		}
		
		if (state[SDL_SCANCODE_F] && coolDownFireTime == 0) {
			
			playSound(11);
			fireDuration = finalTime;
			spawnFire(&mapPhase5, wizard.direction, wizard.x, wizard.y);
			deFreezeCorrect = deFreezeCrystal (&mapPhase5, &wizard, fireDuration, finalTime, which);
			if(deFreezeCorrect == 1){
				
				spawnNexus(&mapPhase5, which);
				deFreezeCorrect = 0;
				
			}
			coolDownFireTime = finalTime;
		}
		
		if (finalTime <= (fireDuration + 50) && fireDuration != 0) {
			
			spawnFire(&mapPhase5, wizard.direction, wizard.x, wizard.y);
			deFreezeCorrect = deFreezeCrystal (&mapPhase5, &wizard, fireDuration, finalTime, which);
			if(deFreezeCorrect == 1){
				
				spawnNexus(&mapPhase5, which);
				deFreezeCorrect = 0;
				
			}
			
		} else {
			
			spawnFire(&mapPhase5, wizard.direction, -100, -100);
			fireDuration = 0;
		}
		
		if (finalTime >= (coolDownFireTime + 100) && (coolDownFireTime) != 0) {
			
			coolDownFireTime = 0;
		}
		
		if(timeStopTime != 0)move(state, &wizard, &mapPhase5, &lastTIME, 75);
		else if(reverseMove == 0) move(state, &wizard, &mapPhase5, &lastTIME, 150);
		else reverseMoves(state, &wizard, &mapPhase5, &lastTIME, 150);
		
		if (timeStopTime == 0) eatPill(&mapPhase5, &wizard, &lightning);
		
		for (i = 0; i < 8; i++) {
			
			if(which[0] == 0 && (i <= 1)) continue; 
			if(which[1] == 0 && (i == 2 || i == 3)) continue; 
			if(which[2] == 0 && (i == 4 || i == 5)) continue; 
			if(which[3] == 0 && (i == 6 || i >= 7)) continue; 
						
			if(shield != 1) over -= gameOver(&wizard, &mapPhase5, monsters[i].x, monsters[i].y, mapPhase5.imageSize, mapPhase5.imageSize);

			if(preOver != over) shield = 1;
		}
		
		if (state[SDL_SCANCODE_E] && coolDownStopTime == 0 && which[2] > 0){
			
			stopTimeMode();
			
			playSound(13);
			
			stop = 1;
		
			timeStopTime = finalTime;
		
		}
		
		if((finalTime + auxTime) >= (timeStopTime + 70) && timeStopTime != 0){
			
			makeTextures();
			
			stop = 0;
			
			timeStopTime = 0;
			
			coolDownStopTime = finalTime;
			
			reverseMove = finalTime;
		}
		
		if(finalTime == (reverseMove + 150) && reverseMove != 0) reverseMove = 0;
		if(finalTime >= (coolDownStopTime + 300) && coolDownStopTime != 0) coolDownStopTime = 0;	
	}
	
	saveData(over, finalTime, 1);
	changeStaticsMap();
	
	freeMap(&mapPhase5);
	
	if(missing == 0){
		option = winningScreen();
		if(option == 0){
			printScreen(&mapPhase5, &wizard, monsters, numClones, 0, beak, shield);
			return 0;
		}else{
			return 1;
		}
	}else{
		
		option = gameOverScreen();
		if(option == 0){
			printScreen(&mapPhase5, &wizard, monsters, numClones, 0, beak, shield);
			
			return -1;
			
		}else{
			
			return 0;
			
		}	
	}
}
