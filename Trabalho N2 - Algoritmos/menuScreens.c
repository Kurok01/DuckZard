#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "interface.h"

SDL_Texture *mainScreenImg[4];
SDL_Texture *pauseScreenImg[4];

SDL_Rect screenSize;

void makeScreenTextures(){
	int i;
	char mainScreenPath[] = "assets\\MainScreen .png";
	char pauseScreenPath[] = "assets\\PauseScreen .png";
	
	for(i = 0; i < 4; i++){
		mainScreenPath[17] = (i+49);
		pauseScreenPath[18] = (i+49);
		
		mainScreenImg[i] = takeImage(mainScreenPath);
		pauseScreenImg[i] = takeImage(pauseScreenPath);
	}
}

void mainScreen(int selection){
	
	int height, width, imageSize, x, y;
	
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

void pauseScreen(int selection){

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, pauseScreenImg[selection-1], NULL, &screenSize);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(100);
}
