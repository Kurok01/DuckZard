#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "structs.h"
#include "mapFunctions.h"
#include "interface.h"

SDL_Texture *wallImg[5];
SDL_Texture *duckImg[4][2];
SDL_Texture *backgroundImg[5];
SDL_Texture *monsterImg[5];
SDL_Texture *dragonImg[2];
SDL_Texture *portalImg[2];
SDL_Texture *externalFireImg;
SDL_Texture *middleFireImg;
SDL_Texture *internalFireImg;
SDL_Texture *thunderImg;
SDL_Texture *hotdogImg;
SDL_Texture *lightningPillImg;
SDL_Texture *lightningProjectileImg;
SDL_Texture *fireballProjectileImg;
SDL_Texture *ogreCloneImg;
SDL_Texture *sandImg;
SDL_Texture *woodImg;

SDL_Rect backGroundImage, dragonImage[2], lightningImage[2];

Mix_Music *soundTrack;
Mix_Chunk *eatingSound;
Mix_Chunk *portalSound;
Mix_Chunk *dragonSound;
Mix_Chunk *thunderSound;
Mix_Chunk *timeStopSound;

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
	
	thunderSound = Mix_LoadWAV("SoundEffects\\ThunderSoundEffect.wav");
	
	if (thunderSound == NULL) {
		
		printf ("Error to open thunder sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	dragonSound = Mix_LoadWAV("SoundEffects\\DragonSoundEffect.wav");
	
	if (dragonSound == NULL) {
		
		printf ("Error to open dragon sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	timeStopSound = Mix_LoadWAV("SoundEffects\\timeStopEffect.wav");
	
	Mix_VolumeChunk(eatingSound, 2);
	Mix_VolumeChunk(portalSound, 64);
	Mix_VolumeChunk(thunderSound, 64);
	Mix_VolumeChunk(dragonSound, 64);
	Mix_VolumeChunk(timeStopSound, 80);
}

void playSound (int soundChoice) {
	
	switch (soundChoice) {
		
		case 1:
			
			Mix_PlayMusic(soundTrack, -1);
			Mix_VolumeMusic(15);
			break;
			
		case 2:
			
			Mix_PlayChannel(-1, eatingSound, 0);
			break;
			
		case 3:
			
			Mix_PlayChannel(-1, portalSound, 0);
			break;
			
		case 4:
			
			Mix_PlayChannel(-1, thunderSound, 0);
			break;
			
		case 5: 
			
			Mix_PlayChannel(-1, dragonSound, 0);
			break;
			
		case 6:
			
			Mix_PlayChannel(-1, timeStopSound, 0);
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
	char pathPortal[] = "assets\\Portal .png";
	char pathMonster[] = "assets\\Monster .png";
	int i, j;
	//Aumentar loop
	for (i = 0; i < 3; i++) {
		
		pathWall[11] = (i+49);
		pathBackground[17] = (i+49);
		pathMonster[14] = (i+49);
	
		wallImg[i] = takeImage(pathWall);
		backgroundImg[i] = takeImage(pathBackground);
		monsterImg[i] =  takeImage(pathMonster);
	
	}
	
	for(i = 0; i < 2; i++){
		pathDragon[13] = (i+49);
		pathPortal[13] = (i+49);
		
		dragonImg[i] = takeImage(pathDragon);
		portalImg[i] = takeImage(pathPortal);

	}
	
	for (i = 0; i < 4; i++) {
		
			pathDuck[12] = (i+48);
		
		for (j = 0; j < 2; j++) {
			
			pathDuck[14] = (j+48);
						
			duckImg[i][j] = takeImage(pathDuck);
		}
	}
		
	externalFireImg = takeImage("assets\\ExternalFire.png");
	middleFireImg = takeImage ("assets\\MiddleFire.png");
	internalFireImg = takeImage("assets\\InternalFire.png");
	thunderImg = takeImage("assets\\Thunder.png");
	lightningPillImg = takeImage("assets\\LightningPill.png");
	hotdogImg = takeImage("assets\\Hotdog.png");
	lightningProjectileImg = takeImage("assets\\LightningProjectile.png");
	sandImg = takeImage("assets\\sand.png");
	woodImg = takeImage("assets\\wood.png");
	/*fireballProjectileImg = takeImage("assets\\FireballProjectile.png");
	ogreCloneImg = takeImage("assets\\OgreClone.png");*/
}


int dragonSpawn(Map_t *map ,int *dragonCountDown, int *lightning, Role_t *wizard, Ogre_t ogres[], int beak, int qtd){
	int over = 0, i, j, temp = 2;
	
	if (*lightning != 0) *lightning += (temp * 100);
	
	if (*dragonCountDown > 0) *dragonCountDown += temp;
	
	for (i = 0; i < 2; i++) {
    	
    	if (i == 0) {
    		
    		dragonImage[i].x = -(map->screenWidth + map->outOfLimitsX) + *dragonCountDown;
	    	dragonImage[i].y = map->outOfLimitsY;
	    	dragonImage[i].w = map->screenWidth;
	    	dragonImage[i].h = map->screenHeight / 2;
	    	
	    	lightningImage[i].x = (map->screenWidth + (map->outOfLimitsX * 2)) - *lightning;
	    	lightningImage[i].y = map->outOfLimitsY;
	    	lightningImage[i].w = map->screenWidth;
	    	lightningImage[i].h = map->screenHeight / 2;
	    	
	    	if (lightningImage[i].x <= (dragonImage[i].x + map->screenWidth)) {
	    	
				dragonImage[i].x = (lightningImage[i].x-1) - map->screenWidth;
			}
	    	
	    	if (dragonImage[i].x  >= map->screenWidth || lightningImage[i].x <= -(map->screenWidth)) {
	    		
	    		if ((*lightning) != 0 && (*dragonCountDown) == 0) *dragonCountDown = -1; 
	    		else *dragonCountDown = 0;
	    		
	    		dragonImage[i].x = -(map->screenWidth + map->outOfLimitsX) + *dragonCountDown;
	    		
	    		*lightning = 0;
	    		lightningImage[i].x = (map->screenWidth + map->outOfLimitsX) - (*lightning);
	    		
	    		temp++;
			} 
	    	
			over = gameOver(wizard, map, dragonImage[i].x, dragonImage[i].y, (map->screenWidth - 100), (map->screenHeight / 2));
			
		} else {
	
    		dragonImage[i].x = (map->screenWidth + (map->outOfLimitsX * 2)) - *dragonCountDown;
	    	dragonImage[i].y = (map->screenHeight / 2) + map->outOfLimitsY;
	    	dragonImage[i].w = map->screenWidth;
	    	dragonImage[i].h = map->screenHeight / 2;
	    	
	    	lightningImage[i].x = -(map->screenWidth + map->outOfLimitsX) + *lightning;
	    	lightningImage[i].y = (map->screenHeight / 2) + map->outOfLimitsY;
	    	lightningImage[i].w = map->screenWidth;
	    	lightningImage[i].h = map->screenHeight / 2;
	    	
	    	if ((lightningImage[i].x + map->screenWidth) >= dragonImage[i].x){
	    	
				dragonImage[i].x = lightningImage[i].x + map->screenWidth + 1;
			}
	    	
	    	if (dragonImage[i].x <= -(map->screenWidth) || lightningImage[i].x >= map->screenWidth) {
	    		
	    		if ((*lightning) != 0 && (*dragonCountDown) == 0) *dragonCountDown = -1; 
	    		else *dragonCountDown = 0;
	    		dragonImage[i].x = (map->screenWidth + map->outOfLimitsX) - *dragonCountDown;
	    		
	    		*lightning = 0;
	    		lightningImage[i].x = -(map->screenWidth + map->outOfLimitsX) + (*lightning);
			}
	    
			over = gameOver(wizard, map, dragonImage[i].x, dragonImage[i].y, (map->screenWidth - 100), (map->screenHeight / 2));
	    }
	    
	    if (over == 1) break;
	}
	
	printScreen(map, wizard, ogres, qtd , 1, beak);
	
	return over;
}

void stopTimeMode(){
	
	monsterImg[2] = takeImage("assets\\Monster3O.png");
	hotdogImg = takeImage("assets\\HotdogO.png");
	sandImg = takeImage("assets\\sandO.png");
	woodImg = takeImage("assets\\woodO.png");
	wallImg[2] = takeImage("assets\\wall3O.png");
	backgroundImg[2] = takeImage("assets\\Background3O.png");
	
}

void printScreen (Map_t *map, Role_t *wizard, Ogre_t ogres[], int qtd ,int phase, int beak) {
	
	int imageSize, height, width;
	int i, j, k = 0;
	int x, y;
	static int tempLimits = 0;
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
				
				if (beak >= 0) SDL_RenderCopy(renderer, duckImg[wizard->direction][beak], NULL, &position);
				else SDL_RenderCopy(renderer, portalImg[(beak * -1) - 1], NULL, &position);	
			}
			
			else if (map->mapPptr[i][j] == 'O') {
				
				position.x = (ogres[k].x) - (imageSize/2);
				position.y = (ogres[k].y) - (imageSize/2);
				
				SDL_RenderCopy(renderer, monsterImg[phase-1], NULL, &position);
				k++;	
			}
			
			else if (map->mapPptr[i][j] == '+') SDL_RenderCopy(renderer, lightningPillImg, NULL, &position);
			else if (map->mapPptr[i][j] == '=') SDL_RenderCopy(renderer, internalFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '?') SDL_RenderCopy(renderer, middleFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '#') SDL_RenderCopy(renderer, externalFireImg, NULL, &position);
			else if (map->mapPptr[i][j] == '$') SDL_RenderCopy(renderer, thunderImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'S') SDL_RenderCopy(renderer, sandImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'A') SDL_RenderCopy(renderer, woodImg, NULL, &position);
  		}
	}
	
	SDL_RenderCopy(renderer, dragonImg[0], NULL, &dragonImage[0]);
	SDL_RenderCopy(renderer, dragonImg[1], NULL, &dragonImage[1]);
	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage[0]);
	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage[1]);
	
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
