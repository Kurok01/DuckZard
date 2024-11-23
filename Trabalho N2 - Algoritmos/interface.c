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
SDL_Texture *thunderImg;
SDL_Texture *hotdogImg;
SDL_Texture *lightningPillImg;
SDL_Texture *lightningProjectileImg;
SDL_Texture *blizzardImg;
SDL_Texture *freezedImg;
SDL_Texture *freezedHotdogImg;
SDL_Texture *halfFreezedHotdogImg;
SDL_Texture *snowballImg;
SDL_Texture *externalFireImg;
SDL_Texture *middleFireImg;
SDL_Texture *internalFireImg;
SDL_Texture *fireProjectileImg[4];
SDL_Texture *sandImg;
SDL_Texture *woodImg;
SDL_Texture *metalImg;
SDL_Texture *cloneImg;
SDL_Texture *nexusImg[4];

SDL_Rect backGroundImage, dragonImage[2], lightningImage[2], blizzardImage[2], freezedImage, fireProjectileImage, snowBallImage[40], nexusImage[4];

Mix_Music *soundTrack;
Mix_Chunk *eatingSound;
Mix_Chunk *portalSound;
Mix_Chunk *dragonSound;
Mix_Chunk *thunderSound;
Mix_Chunk *blizzardSound;
Mix_Chunk *fireSound;
Mix_Chunk *snowballSound;
Mix_Chunk *timeStopSound;


void initSDL () {
	snowBallImage[0].x = -100;
	
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
	
	blizzardSound = Mix_LoadWAV("SoundEffects\\BlizzardSoundEffect.wav");
	
	if (blizzardSound == NULL) {
		
		printf ("Error to open blizzard sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	fireSound = Mix_LoadWAV("SoundEffects\\FireSoundEffect.wav");
	
	if (fireSound == NULL) {
		
		printf ("Error to open fire sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	snowballSound = Mix_LoadWAV("SoundEffects\\SnowballSoundEffect.wav");
	
	if (snowballSound == NULL) {
		
		printf ("Error to open snowball sound: %s", Mix_GetError());
		
		exit(1);
	}
	
	timeStopSound = Mix_LoadWAV("SoundEffects\\timeStopEffect.wav");
	
	if (timeStopSound == NULL) {
		
		printf ("Error to open time stop sound: %s", Mix_GetError());
	}
	
	Mix_VolumeChunk(eatingSound, 2);
	Mix_VolumeChunk(portalSound, 64);
	Mix_VolumeChunk(thunderSound, 64);
	Mix_VolumeChunk(dragonSound, 64);
	Mix_VolumeChunk(blizzardSound, 64);
	Mix_VolumeChunk(fireSound, 50);
	Mix_VolumeChunk(snowballSound, 32);
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
			
			Mix_PlayChannel(-1, blizzardSound, 0);
			break;
			
		case 7:
			
			Mix_PlayChannel(-1, fireSound, 0);
			break;
			
		case 8:
			
			Mix_PlayChannel(-1, snowballSound, 0);
			break;
			
		case 9:
			
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
	char pathFireProjectile[] = "assets\\FireProjectile .png";
	int i, j;
	//Aumentar loop
	for (i = 0; i < 4; i++) {
		
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
			pathFireProjectile[21] = (i+49);
			fireProjectileImg[i] = takeImage(pathFireProjectile);
		
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
	freezedImg = takeImage("assets\\FreezedScreen.png");
	freezedHotdogImg = takeImage("assets\\FreezedHotdog.png");
	halfFreezedHotdogImg = takeImage("assets\\HalfFreezedHotdog.png");
	blizzardImg = takeImage("assets\\Blizzard.png");
	snowballImg = takeImage("assets\\Snowball.png");
	sandImg = takeImage("assets\\sand.png");
	woodImg = takeImage("assets\\wood.png");
	metalImg = takeImage("assets\\cloneTexture.png");
	cloneImg = takeImage("assets\\Monster4C.png");
}

void phase2ElementsSpawn (Map_t *map, int *blizzard, Wizard_t *wizard, Monster_t *monster, int beak, int qtd) {
	
	int i, temp = 5, aux = 5; 
	static int blizzard2, secondRound = 0;
	
	if (*blizzard == 0){
		
		blizzard2 = 0;
		secondRound = 0;
	} 
	
	if((*blizzard) != 0 && (*blizzard) <= 20){
		
		for(i = 0; i < 40; i++){
			
			snowBallImage[i].x = -100;
			snowBallImage[i].y = -100;
			
		}
	}
	
	if (*blizzard != 0) {
		
		blizzard2 += aux;	
		*blizzard += temp;
	}
	
	freezedImage.x =  -(map->screenWidth + (map->outOfLimitsX * 2));
   	freezedImage.y = map->outOfLimitsY;
    freezedImage.w = map->screenWidth;
   	freezedImage.h =  map->screenHeight;
	
	blizzardImage[0].x = (map->screenWidth + (map->outOfLimitsX * 2)) - *blizzard;
	blizzardImage[0].y = map->outOfLimitsY;
	blizzardImage[0].w = map->screenWidth;
	blizzardImage[0].h = map->screenHeight;
	
	if (secondRound == 0) {
	   	
		blizzardImage[1].x = (map->screenWidth * 2) + (map->outOfLimitsX * 2) - blizzard2;
		blizzardImage[1].y = map->outOfLimitsY;
		blizzardImage[1].w = map->screenWidth;
		blizzardImage[1].h = map->screenHeight;
		
	} else {

		blizzardImage[1].x = (map->screenWidth) + (map->outOfLimitsX * 2) - blizzard2;
		blizzardImage[1].y = map->outOfLimitsY;
		blizzardImage[1].w = map->screenWidth;
		blizzardImage[1].h = map->screenHeight;
		
	}
	
	if (*blizzard != 0) {
		
	   	if (blizzardImage[0].x <= (-(map->screenWidth + (map->outOfLimitsX * 2)))) {
	   		
	   	   *blizzard = 1;
	   		blizzardImage[0].x = (map->screenWidth + map->outOfLimitsX) - *blizzard;
			blizzardImage[0].y = map->outOfLimitsY;
			blizzardImage[0].w = map->screenWidth;
			blizzardImage[0].h = map->screenHeight;
		}
		   
		if (blizzardImage[1].x <= (-(map->screenWidth + (map->outOfLimitsX * 2)))) {
		
			blizzard2 = 1;
			blizzardImage[1].x = (map->screenWidth) + (map->outOfLimitsX * 2) - blizzard2;
			blizzardImage[1].y = map->outOfLimitsY;
			blizzardImage[1].w = map->screenWidth;
			blizzardImage[1].h = map->screenHeight;
			secondRound = 1;
		}
	   	
	   	freezedImage.x =  map->outOfLimitsX;
    	freezedImage.y = map->outOfLimitsY;
    	freezedImage.w = map->screenWidth;
    	freezedImage.h =  map->screenHeight;
	}
	
	printScreen(map, wizard, monster, 8, 2, beak);
}

void spawnFire (Map_t *map, int direction, float x, float y) {
	
	if (direction == 0) {
		
		fireProjectileImage.x = x + map->imageSize;
		fireProjectileImage.y = y;
		fireProjectileImage.w = map->imageSize;
		fireProjectileImage.h = map->imageSize;
	
	} else if (direction == 1) {
		
		fireProjectileImage.x = x - map->imageSize;
		fireProjectileImage.y = y;
		fireProjectileImage.w = map->imageSize;
		fireProjectileImage.h = map->imageSize;
		
	} else if (direction == 2) {
		
		fireProjectileImage.x = x;
		fireProjectileImage.y = y + map->imageSize;
		fireProjectileImage.w = map->imageSize;
		fireProjectileImage.h = map->imageSize;
		
	} else if (direction == 3) {
		
		fireProjectileImage.x = x;
		fireProjectileImage.y = y - map->imageSize;
		fireProjectileImage.w = map->imageSize;
		fireProjectileImage.h = map->imageSize;
	}
}

int phase1ElementsSpawn (Map_t *map , int *dragonCountDown, int *lightning, Wizard_t *wizard, Monster_t ogres[], int beak, int qtd) {
	
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

void spawnSnowBall(Map_t *map, Monster_t *snowBall, int *numSnowBalls){
	int x;
	static int i = 0, j =1;
	
	srand(time(0) + (i * j));
	
	i += 2;
	j += 7;
	
	if(i >= 10000) i = 0;
	if(j >= 10000) j = 1;
	
	x = rand() % map->width;
	if(x == 0) x = 1;
	
	snowBall[*numSnowBalls].x = (x * map->imageSize) + map->outOfLimitsX;
	snowBall[*numSnowBalls].y = -(map->outOfLimitsY);
	snowBall[(*numSnowBalls) + 1].x = -100;
	
	snowBallImage[*numSnowBalls].x = (x * map->imageSize) + map->outOfLimitsX;
	snowBallImage[*numSnowBalls].y = -(map->outOfLimitsY);
	snowBallImage[*numSnowBalls].w = map->imageSize;
	snowBallImage[*numSnowBalls].h = map->imageSize;
	snowBallImage[(*numSnowBalls) + 1].x = -100;
	
	(*numSnowBalls)++;
	
}


void moveSnowBall(Map_t *map ,Monster_t *snowBall, int *numSnowBalls){
	int i = 0;
	
	while(snowBallImage[i].x != -100){
		
			snowBall[i].y += 10;
			snowBallImage[i].y += 10;
			i++;
			printf("%.1f\n", snowBall[i].y);
			if(snowBall[i].y >= (map->screenHeight + (map->outOfLimitsY * 2))){
				snowBall[i].x = snowBall[(*numSnowBalls)-1].x;
				snowBall[i].y = snowBall[(*numSnowBalls)-1].y;
				
				snowBallImage[i].x = snowBall[(*numSnowBalls)-1].x;
				snowBallImage[i].y = snowBall[(*numSnowBalls)-1].y;
				
				(*numSnowBalls)--;
				snowBallImage[(*numSnowBalls)-1].x = -100;
				snowBall[(*numSnowBalls)-1].x = -100;
			}
	}
}

void spawnNexus(Map_t *map, int type, int which[4]){
	
	nexusImage[0].x = (3 * map->imageSize) + map->outOfLimitsX;
	nexusImage[1].x = (47 * map->imageSize) + map->outOfLimitsX;
	nexusImage[2].x = (3 * map->imageSize) + map->outOfLimitsX;
	nexusImage[3].x = (47 * map->imageSize) + map->outOfLimitsX;
	
	nexusImage[0].y = (2 * map->imageSize) + map->outOfLimitsY;
	nexusImage[1].y = (24 * map->imageSize) + map->outOfLimitsY;
	nexusImage[2].y = (2 * map->imageSize) + map->outOfLimitsY;
	nexusImage[3].y = (24 * map->imageSize) + map->outOfLimitsY;
	
	char nexusPhase1[] = "assets\\IcePhase1_ .png";
	char nexusPhase2[] = "assets\\IcePhase2_ .png";
	char nexusPhase3[] = "assets\\IcePhase3_ .png";
	char nexusPhase4[] = "assets\\IcePhase4_ .png";
	
	nexusPhase1[17] = (which[0] + 48);
	nexusPhase2[17] = (which[1] + 48);
	nexusPhase3[17] = (which[2] + 48);
	nexusPhase4[17] = (which[3] + 48);
	
	nexusImg[0] = takeImage(nexusPhase1);
	nexusImg[1] = takeImage(nexusPhase2);
	nexusImg[2] = takeImage(nexusPhase3);
	nexusImg[3] = takeImage(nexusPhase4);
}

void printScreen (Map_t *map, Wizard_t *wizard, Monster_t monster[], int qtd ,int phase, int beak) {
	
	int imageSize, height, width;
	int i, j, k = 0, l = 0;
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
			
			monster[i].x = ((monster[i].x * imageSize) + x);
			monster[i].y = ((monster[i].y * imageSize) + y);
		}
		
		tempLimits++;
	}
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			if(j == && (i == 2 || i == 24)) l = 0;
			if(j == && (i == 2 || i == 24)) l = 1;
			if(j == && (i == 2 || i == 24)) l = 2;
			if(j == && (i == 2 || i == 24)) l = 3;
			
			SDL_Rect position;
			position.x = (j * imageSize) + x;
			position.y = (i * imageSize) + y;
			position.w = (imageSize);
			position.h = (imageSize);
			
			if (map->mapPptr[i][j] == '*') SDL_RenderCopy(renderer, wallImg[phase - 1], NULL, &position);
			else if (map->mapPptr[i][j] == ' ') SDL_RenderCopy(renderer, hotdogImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'I') SDL_RenderCopy(renderer, freezedHotdogImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'H') SDL_RenderCopy(renderer, halfFreezedHotdogImg, NULL, &position);
			else if (map->mapPptr[i][j] == 'D') {
				
				position.x = wizard->x;
				position.y = wizard->y;
				
				if(wizard->type == 'D'){
			
					if (beak >= 0) SDL_RenderCopy(renderer, duckImg[wizard->direction][beak], NULL, &position);
					else SDL_RenderCopy(renderer, portalImg[(beak * -1) - 1], NULL, &position);	
			
				}else{
					
					SDL_RenderCopy(renderer, monsterImg[3], NULL, &position);
					
				}
			}
			
			else if (map->mapPptr[i][j] == 'O') {
				
				position.x = (monster[k].x);
				position.y = (monster[k].y);
				
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
			else if (map->mapPptr[i][j] == 'M') SDL_RenderCopy(renderer, metalImg, NULL, &position);
  		}
	}
	
	for(i = k; i < qtd; i++ ){
			SDL_Rect position;
		
			position.x = (monster[i].x);
			position.y = (monster[i].y);
			position.w = (imageSize);
			position.h = (imageSize);
				
			SDL_RenderCopy(renderer, cloneImg, NULL, &position);
	}
	
	SDL_RenderCopy(renderer, dragonImg[0], NULL, &dragonImage[0]);
	SDL_RenderCopy(renderer, dragonImg[1], NULL, &dragonImage[1]);
	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage[0]);
	SDL_RenderCopy(renderer, lightningProjectileImg, NULL, &lightningImage[1]);
	SDL_RenderCopy(renderer, fireProjectileImg[wizard->direction], NULL, &fireProjectileImage);
	SDL_RenderCopy(renderer, blizzardImg, NULL, &blizzardImage[0]);
	SDL_RenderCopy(renderer, blizzardImg, NULL, &blizzardImage[1]);
	SDL_RenderCopy(renderer, freezedImg, NULL, &freezedImage);
	SDL_RenderCopy(renderer, nexusImg[0], NULL, &nexusImage[0]);
	SDL_RenderCopy(renderer, nexusImg[1], NULL, &nexusImage[1]);
	SDL_RenderCopy(renderer, nexusImg[2], NULL, &nexusImage[2]);
	SDL_RenderCopy(renderer, nexusImg[3], NULL, &nexusImage[3]);
	i = 0;
	
	while(snowBallImage[i].x != -100){

		SDL_RenderCopy(renderer, snowballImg, NULL, &snowBallImage[i]);
		i++;
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
	
//Destuir tudo
/*
	SDL_DestroyTexture(hotdogImg);
	SDL_DestroyTexture(internalFireImg);
	SDL_DestroyTexture(middleFireImg);
	SDL_DestroyTexture(externalFireImg);
	SDL_DestroyTexture(thunderImg);
	SDL_DestroyTexture(lightningProjectileImg);
	SDL_DestroyTexture(lightningPillImg);
	SDL_DestroyTexture(fireProjectileImg);
	SDL_DestroyTexture(snowballImg);
	SDL_DestroyTexture(blizzardImg);
	SDL_DestroyTexture(freezedImg);*/
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
} 
