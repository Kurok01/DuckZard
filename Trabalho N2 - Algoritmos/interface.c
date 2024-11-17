#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "structs.h"
#include "mapFunctions.h"

SDL_Texture *wallImg[5];
SDL_Texture *duckImg[4][2];
SDL_Texture *backgroundImg[5];
SDL_Texture *ogreImg;
SDL_Texture *dragonImg[2];
SDL_Texture *externalFireImg;
SDL_Texture *middleFireImg;
SDL_Texture *internalFireImg;
SDL_Texture *thunderImg;
SDL_Texture *hotdogImg;
SDL_Texture *lightningProjectileImg;
SDL_Texture *fireballProjectileImg;
SDL_Texture *ogreCloneImg;

SDL_DisplayMode displayMode;

SDL_Renderer *renderer;

SDL_Window *window;

void initSDL () {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		
		printf ("Error to init SDL: %s", SDL_GetError());
		
		exit(1);
	}
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		
		printf ("Erro to init SDL_Image: %s", IMG_GetError());
		
		SDL_Quit();
		exit(1);
	}
	
	SDL_GetCurrentDisplayMode(0, &displayMode);
	
	window = SDL_CreateWindow("DuckZard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);
	
	if (!window) {
		
		printf ("Error to init window: %s", SDL_GetError());
		
		IMG_Quit();
		SDL_Quit();
		exit(1);
	}
	
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!renderer) {
		
		printf ("Erro ao criar renderizador: %s", SDL_GetError());
		
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		exit(1);
	}
}

SDL_Texture *takeImage (char pathImage[]) {
	
	SDL_Surface *image = IMG_Load(pathImage);
	
	if (!image) {
		
		printf ("Error to open image: %s", IMG_GetError());
		
		exit (1);
	}
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
	
	SDL_FreeSurface(image);
	
	return texture;
}

void makeTextures () {
	
	char pathWall[] = "assets\\Wall .png";
	char pathBackground[] = "assets\\Background .png";
	char pathDuck[] = "assets\\Duck( , ).png";
	char pathDragon[] = "assets\\Dragon .png";
	int i, j;
	//Aumentar loop
	for (i = 0; i < 2; i++) {
		
		pathWall[11] = (i+49);
		pathBackground[17] = (i+49);
		pathDragon[13] = (i+49);
		wallImg[i] = takeImage(pathWall);
		backgroundImg[i] = takeImage(pathBackground);
		dragonImg[i] = takeImage(pathDragon);
		
	}
	
	for (i = 0; i < 4; i++) {
		
			pathDuck[12] = (i+48);
		
		for (j = 0; j < 2; j++) {
			
			pathDuck[14] = (j+48);
						
			duckImg[i][j] = takeImage(pathDuck);
		}
	}
		
	ogreImg = takeImage("assets\\Ogre.png");
	externalFireImg = takeImage("assets\\ExternalFire.png");
	middleFireImg = takeImage ("assets\\MiddleFire.png");
	internalFireImg = takeImage("assets\\InternalFire.png");
	thunderImg = takeImage("assets\\Thunder.png");
	hotdogImg = takeImage("assets\\Hotdog.png");
	/*lightningProjectileImg = takeImage("assets\\LightningProjectile.png");
	fireballProjectileImg = takeImage("assets\\FireballProjectile.png");
	dragonImg = takeImage("assets\\Dragon.png");
	ogreCloneImg = takeImage("assets\\OgreClone.png");*/
}

void printScreen (Map_t *map, Role_t *wizard, Role_t ogres[], int qtd, int phase, int beak, int *dragonCountDown) {
	
	int imageSize, height, width;
	int i, j, k = 0;
	int x, y;
	static int tempLimits = 0;
	static int temp = 1;
	
	height = displayMode.h / map->height;
	width = displayMode.w / map->width;
	
	if (height >= width) imageSize = width;
	else imageSize = height;
	
	x = (displayMode.w - (imageSize * map->width)) / 2;
	y = (displayMode.h - (imageSize * map->height)) / 2;
	
	SDL_RenderClear(renderer);
	
	map->screenWidth = displayMode.w - (x * 2);
	map->screenHeight = displayMode.h - (y * 2);
	map->imageSize = imageSize;
	
	map->outOfLimitsX = x;
	map->outOfLimitsY = y;
	
	SDL_Rect backGroundImage, dragonImage;

    backGroundImage.x = x;
    backGroundImage.y = y;
    backGroundImage.w = map->screenWidth;
    backGroundImage.h = map->screenHeight;

    SDL_RenderCopy(renderer, backgroundImg[phase - 1], NULL, &backGroundImage);

	if (tempLimits == 0) {
		
		wizard->x = (wizard->x * imageSize) + x;
		wizard->y = (wizard->y * imageSize) + y; 
		
		for(i = 0; i < qtd; i++){
			
			ogres[i].x = (ogres[i].x * imageSize) + x;
			ogres[i].y = (ogres[i].y * imageSize) + y;
		}
		
		tempLimits++;
	}
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			SDL_Rect position;
			position.x = (j * imageSize) + x;
			position.y = (i * imageSize) + y;
			position.w = (imageSize);
			position.h = (imageSize);
			
			if (map->mapPptr[i][j] == '*') SDL_RenderCopy(renderer, wallImg[phase - 1], NULL, &position);
			else if (map->mapPptr[i][j] == ' ') SDL_RenderCopy(renderer, hotdogImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'D') {
				
				position.x = wizard->x;
				position.y = wizard->y;
			
				SDL_RenderCopy(renderer, duckImg[wizard->direction][beak], NULL, &position);	
			}
			else if (map->mapPptr[i][j] == 'O'){
				
				position.x = ogres[k].x;
				position.y = ogres[k].y;
				
				SDL_RenderCopy(renderer, ogreImg, NULL, &position);
				k++;
				
			}
			else if (map->mapPptr[i][j] == '+') SDL_RenderCopy(renderer, internalFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '?') SDL_RenderCopy(renderer, middleFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '#') SDL_RenderCopy(renderer, externalFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '$') SDL_RenderCopy(renderer, thunderImg, NULL, &position);
  		}
	}
	
	if (*dragonCountDown != 0) *dragonCountDown += temp;
	
	for (i = 0; i < 2; i++) {
    	
    	if (i == 0) {
    		
    		dragonImage.x = -(map->screenWidth + x) + *dragonCountDown;
	    	dragonImage.y = y;
	    	dragonImage.w = map->screenWidth;
	    	dragonImage.h = map->screenHeight / 2;
	    	
	    	if (dragonImage.x >= map->screenWidth * 2) {
	    		
	    		*dragonCountDown = 0;
	    		dragonImage.x = -(map->screenWidth + x) + *dragonCountDown;
	    		
	    		temp++;
			}  
	    	
	    	SDL_RenderCopy(renderer, dragonImg[i], NULL, &dragonImage);
			
		} else {
	
    		dragonImage.x = (map->screenWidth + x) - *dragonCountDown;
	    	dragonImage.y = (map->screenHeight / 2) + y;
	    	dragonImage.w = map->screenWidth;
	    	dragonImage.h = map->screenHeight / 2;
	    	
	    	if (dragonImage.x <= -(map->screenWidth * 2)) {
	    		
	    		*dragonCountDown = 0;
	    		dragonImage.x = (map->screenWidth + x) - *dragonCountDown;
			}
	    	
	    	SDL_RenderCopy(renderer, dragonImg[i], NULL, &dragonImage);
	    }
	}
	
	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void freeSDL () {
	
	int i, j;
	
	//Aumentar loop
	for (i = 0; i < 2; i++) {
		
		SDL_DestroyTexture(backgroundImg[i]);
		SDL_DestroyTexture(wallImg[i]);
		SDL_DestroyTexture(dragonImg[i]);
	}
	
	for (i = 0; i < 4; i++) {
		
		for (j = 0; j < 2; j++) {
			
			SDL_DestroyTexture(duckImg[i][j]);
		}
	}
	

	SDL_DestroyTexture(hotdogImg);
	SDL_DestroyTexture(ogreImg);;
	SDL_DestroyTexture(internalFireImg);
	SDL_DestroyTexture(middleFireImg);
	SDL_DestroyTexture(externalFireImg);
	SDL_DestroyTexture(thunderImg);

	/*SDL_DestroyTexture(ogreCloneImg);
	SDL_DestroyTexture(dragonImg);
	SDL_DestroyTexture(lightningProjectileImg);
	SDL_DestroyTexture(fireballProjectileImg);*/
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
} 
