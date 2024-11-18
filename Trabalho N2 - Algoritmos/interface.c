#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
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
SDL_Texture *lightningPillImg;
SDL_Texture *lightningProjectileImg;
SDL_Texture *fireballProjectileImg;
SDL_Texture *ogreCloneImg;

Mix_Music *soundTrack;
Mix_Chunk *eatingSound;
Mix_Chunk *portalSound;

SDL_DisplayMode displayMode;

SDL_Renderer *renderer;

SDL_Window *window;

void initSDL () {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		
		printf ("Error to init SDL: %s", SDL_GetError());
		
		exit(1);
	}
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		
		printf ("Error to init SDL_Image: %s", IMG_GetError());
		
		SDL_Quit();
		exit(1);
	}
	
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		
		printf ("Error to init SDL: %s", SDL_GetError());
		
		exit(1);
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		
		printf ("Error to init SDL_Mixer: %s", Mix_GetError());
		
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

void initSound () {
	
	soundTrack = Mix_LoadMUS("SoundEffects\\SoundTrack.mp3");
	
	if (soundTrack == NULL) {
		
		printf ("Error to open SoundTrack: %s", Mix_GetError());
		
		exit(1);
	}
	
	eatingSound = Mix_LoadWAV("SoundEffects\\EatingSoundEffect.wav");
	
	if (eatingSound == NULL) {
		
		printf ("Error to open eating sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	portalSound = Mix_LoadWAV("SoundEffects\\PortalSoundEffect.wav");
	
	if (portalSound == NULL) {
		
		printf ("Error to open portal sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	Mix_Volume(-1, 2);
}

void playSound (int soundChoice) {
	
	switch (soundChoice) {
		
		case 1:
			
			Mix_PlayMusic(soundTrack, -1);
			Mix_VolumeMusic(28);
			break;
			
		case 2:
			
			Mix_PlayChannel(-1, eatingSound, 0);
			break;
			
		case 3:
			
			Mix_PlayChannel(-1, portalSound, 0);
			break;
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
	lightningPillImg = takeImage("assets\\LightningPill.png");
	hotdogImg = takeImage("assets\\Hotdog.png");
	lightningProjectileImg = takeImage("assets\\LightningProjectile.png");
	/*fireballProjectileImg = takeImage("assets\\FireballProjectile.png");
	ogreCloneImg = takeImage("assets\\OgreClone.png");*/
}

int printScreen (Map_t *map, Role_t *wizard, Ogre_t ogres[], int qtd, int phase, int beak, int *dragonCountDown, int *lightning) {
	
	int imageSize, height, width;
	int i, j, k = 0;
	int x, y;
	static int tempLimits = 0;
	static int temp = 2;
	int over = 0;
	
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
	
	SDL_Rect backGroundImage, dragonImage, lightningImage;

    backGroundImage.x = x;
    backGroundImage.y = y;
    backGroundImage.w = map->screenWidth;
    backGroundImage.h = map->screenHeight;

    SDL_RenderCopy(renderer, backgroundImg[phase - 1], NULL, &backGroundImage);

	if (tempLimits == 0) {
		
		wizard->x = (wizard->x * imageSize) + x;
		wizard->y = (wizard->y * imageSize) + y; 
		
		for(i = 0; i < qtd; i++){
			
			ogres[i].x = ((ogres[i].x * imageSize) + x);
			ogres[i].y = ((ogres[i].y * imageSize) + y);
			
			ogres[i].x += (imageSize/2);
			ogres[i].y += (imageSize/2);
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
				
				position.x = (ogres[k].x) - (imageSize/2);
				position.y = (ogres[k].y) - (imageSize/2);
				
				SDL_RenderCopy(renderer, ogreImg, NULL, &position);
				k++;
				
			}
			else if (map->mapPptr[i][j] == '+') SDL_RenderCopy(renderer, lightningPillImg, NULL, &position);
			else if (map->mapPptr[i][j] == '?') SDL_RenderCopy(renderer, middleFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '#') SDL_RenderCopy(renderer, externalFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '$') SDL_RenderCopy(renderer, thunderImg, NULL, &position);
  		}
	}
	
	if(*lightning != 0) *lightning += temp;
	
	if (*dragonCountDown != 0) *dragonCountDown += temp;
	
	for (i = 0; i < 2; i++) {
    	
    	if (i == 0) {
    		
    		dragonImage.x = -(map->screenWidth + x) + *dragonCountDown;
	    	dragonImage.y = y;
	    	dragonImage.w = map->screenWidth;
	    	dragonImage.h = map->screenHeight / 2;
	    	
	    	lightningImage.x = (map->screenWidth + x) - *lightning;
	    	lightningImage.y = y;
	    	lightningImage.w = map->screenWidth;
	    	lightningImage.h = map->screenHeight / 2;
	    	
	    	if (lightningImage.x <= (dragonImage.x + map->screenWidth)){
	    	
				dragonImage.x = (lightningImage.x-1) - map->screenWidth;
			
			}
	    	
	    	if (dragonImage.x  >= map->screenWidth || lightningImage.x <= -(map->screenWidth)) {
	    		
	    		*dragonCountDown = 0;
	    		dragonImage.x = -(map->screenWidth + x) + *dragonCountDown;
	    		
	    		*lightning = 0;
	    		lightningImage.x = (map->screenWidth + x) - (*lightning);
	    		
	    		temp++;
			} 
	    	
			over = gameOver(wizard, map, dragonImage.x, dragonImage.y, (map->screenWidth - 100), (map->screenHeight / 2));
	    	
	    	SDL_RenderCopy(renderer, dragonImg[i], NULL, &dragonImage);
	    	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage);
			
		} else {
	
    		dragonImage.x = (map->screenWidth + x) - *dragonCountDown;
	    	dragonImage.y = (map->screenHeight / 2) + y;
	    	dragonImage.w = map->screenWidth;
	    	dragonImage.h = map->screenHeight / 2;
	    	
	    	lightningImage.x = -(map->screenWidth + x) + *lightning;
	    	lightningImage.y = (map->screenHeight / 2) + y;
	    	lightningImage.w = map->screenWidth;
	    	lightningImage.h = map->screenHeight / 2;
	    	
	    	if ((lightningImage.x + map->screenWidth) >= dragonImage.x){
	    	
				dragonImage.x = lightningImage.x + map->screenWidth + 1;
			}
	    	
	    	if (dragonImage.x <= -(map->screenWidth) || lightningImage.x >= map->screenWidth) {
	    		
	    		*dragonCountDown = 0;
	    		dragonImage.x = (map->screenWidth + x) - *dragonCountDown;
	    		
	    		*lightning = 0;
	    		lightningImage.x = -(map->screenWidth + x) + (*lightning);
			}
	    
			over = gameOver(wizard, map, dragonImage.x, dragonImage.y, (map->screenWidth - 100), (map->screenHeight / 2));
			
	    	SDL_RenderCopy(renderer, dragonImg[i], NULL, &dragonImage);
	    	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage);
	    }
	    
	    if (over == 1) break;
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
	
	return over;
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
	SDL_DestroyTexture(lightningProjectileImg);
	SDL_DestroyTexture(lightningPillImg);

	/*SDL_DestroyTexture(ogreCloneImg);
	SDL_DestroyTexture(dragonImg);
	SDL_DestroyTexture(fireballProjectileImg);*/
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
} 
