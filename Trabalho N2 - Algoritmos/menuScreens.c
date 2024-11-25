#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <time.h>
#include "interface.h"
#include "menuScreens.h"
#include "mapFunctions.h"

SDL_Texture *mainScreenImg[5];
SDL_Texture *pauseScreenImg[4];
SDL_Texture *choosePhaseImg[5][6];
SDL_Texture *winningImg[4];
SDL_Texture *gameOverImg[4];
SDL_Texture *letters[23];
SDL_Texture *numbers[10];
SDL_Texture *statisticsBackGroundImg;

SDL_Rect screenSize;

int imageSize, x, y;

void makeScreenTextures(){
	int i, j;
	char mainScreenPath[] = "assets\\MainScreen .png";
	char pauseScreenPath[] = "assets\\PauseScreen .png";
	char winningScreenPath[] = "assets\\victory .png";
	char gameOverScreenPath[] = "assets\\gameOver .png";
	char pathChoosePhase[] = "assets\\choose _ .png";
	char pathLetter[] = "assets\\ .png";
	char pathNumber[] = "assets\\ .png";
	
	alocMap("statisticsMap.txt", &statisticsMap);
	
	for(i = 0; i < 26; i++){
		pathLetter[7] = (i + 65);
		
		letters[i] = takeImage(pathLetter);
	}
	
	for(i = 0; i < 10; i++){
		pathNumber[7] = (i + 48);
		
		numbers[i] = takeImage(pathNumber);
	}
	
	for(i = 1; i <= 5; i++){
		
		for(j = 0; j <= i; j++){
			
			pathChoosePhase[13] = (i + 48);
			pathChoosePhase[15] = (j + 48);
			
			choosePhaseImg[i-1][j] = takeImage(pathChoosePhase);
			
		}
		
	}
	
	for(i = 0; i < 5; i++){
		mainScreenPath[17] = (i+49);
		
		mainScreenImg[i] = takeImage(mainScreenPath);
	}
	
	for(i = 0; i < 4; i++){
		pauseScreenPath[18] = (i+49);
		winningScreenPath[14] = (i+48);
		gameOverScreenPath[15] = (i+48);
		
		pauseScreenImg[i] = takeImage(pauseScreenPath);
		winningImg[i] = takeImage(winningScreenPath);
		gameOverImg[i] = takeImage(gameOverScreenPath);
	}
	
	statisticsBackGroundImg = takeImage("assets\\staticsBackGroundImg.png");
}

void mainScreen(int selection){
	
	int height, width;
	
	height = displayMode.h / 27;
	width = displayMode.w / 51;
	
	if (height >= width) imageSize = width;
	else imageSize = height;
	
	x = (displayMode.w - (imageSize * 51)) / 2;
	y = (displayMode.h - (imageSize * 27)) / 2;
	
	SDL_RenderClear(renderer);
	
	screenSize.x = x;
	screenSize.y = y;
	screenSize.w = displayMode.w - (x * 2);
	screenSize.h = displayMode.h - (y * 2);
	
	SDL_RenderCopy(renderer, mainScreenImg[selection-1], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
}

void choosePhaseScreen(int phases, int selection){
	
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, choosePhaseImg[phases-1][selection], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
	
}

int winningScreen(){
	const Uint8 *state;
    int  selection = 2;
    float firstTime, secondTime, aux = 0;
    int finalTime, preTime = 1, print, phases = 5, option = 0;
    SDL_Event event;
	
	while(1){
		secondTime = clock();
		aux = secondTime - firstTime;
		aux /= CLOCKS_PER_SEC;
        finalTime = aux * 10;
		
		if(print == 0) printWinningScreen(selection);
		else printWinningScreen(1);
		
		if(finalTime > (preTime + 4)){
		    preTime = finalTime;
		
		    if(print == 0) print = 1;
		    else print = 0;
		}
		
		while(SDL_PollEvent(&event));
		
		state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_W]){
		
		    if(selection > 2) selection--;
		    printWinningScreen(selection);
		
		}
		
		if(state[SDL_SCANCODE_S]){
		
		    if(selection < 4) selection++;
		    printWinningScreen(selection);
		
		}
		
		if(state[SDL_SCANCODE_RETURN] && selection == 2){
		    return 1;
		}
		
		if(state[SDL_SCANCODE_RETURN] && selection == 4){
		    return 0;
		}
	}
}

void printWinningScreen(int selection){
	
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, winningImg[selection-1], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
	
}

int gameOverScreen(){
	const Uint8 *state;
    int  selection = 2;
    float firstTime, secondTime, aux = 0;
    int finalTime, preTime = 1, print, phases = 5, option = 0;
    SDL_Event event;
	
	while(1){
		secondTime = clock();
		aux = secondTime - firstTime;
		aux /= CLOCKS_PER_SEC;
        finalTime = aux * 10;
		
		if(print == 0) printgameOverScreen(selection);
		else printgameOverScreen(1);
		
		if(finalTime > (preTime + 4)){
		    preTime = finalTime;
		
		    if(print == 0) print = 1;
		    else print = 0;
		}
		
		while(SDL_PollEvent(&event));
		
		state = SDL_GetKeyboardState(NULL);
		
		if(state[SDL_SCANCODE_W]){
		
		    if(selection > 2) selection--;
		    printgameOverScreen(selection);
		
		}
		
		if(state[SDL_SCANCODE_S]){
		
		    if(selection < 4) selection++;
		    printgameOverScreen(selection);
		
		}
		
		if(state[SDL_SCANCODE_RETURN] && selection == 2){
		    return 0;
		}
		
		if(state[SDL_SCANCODE_RETURN] && selection == 4){
		    return 1;
		}
	}
}

void printgameOverScreen(int selection){
	
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, gameOverImg[selection-1], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
	
}

void pauseScreen(int selection){

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, pauseScreenImg[selection-1], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
}

void statisticsScreen(){
	
	int i,j;
	
	SDL_RenderClear(renderer);
	
	SDL_RenderCopy(renderer, statisticsBackGroundImg, NULL, &screenSize);
	
	for (i = 0; i < 27; i++) {
		
		for (j = 0; j < 51; j++) {
			
			SDL_Rect position;
			position.x = (j * imageSize) + x;
			position.y = (i * imageSize) + y;
			position.w = (imageSize * 2);
			position.h = (imageSize * 2);
			
			if (statisticsMap.mapPptr[i][j] >= 'A' && statisticsMap.mapPptr[i][j] <= 'Z') SDL_RenderCopy(renderer, letters[(statisticsMap.mapPptr[i][j]) - 65], NULL, &position);
			else if (statisticsMap.mapPptr[i][j] >= '0' && statisticsMap.mapPptr[i][j] <= '9') SDL_RenderCopy(renderer, numbers[(statisticsMap.mapPptr[i][j]) - 48], NULL, &position);
			
  		}
	}
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(16);
}
