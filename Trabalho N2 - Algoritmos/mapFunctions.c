#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "structs.h"

void alocMap (char path[], Map_t *map) {
	
	int i;
	
	FILE *f;
	
	f = fopen (path, "r");
	
	if (f == NULL) {
		
		printf ("Erro ao abrir aqruivo");
	}
	
	fscanf (f, "%d %d ", &(map->width), &(map->height));
	
	map->mapPptr = (char **) malloc (sizeof(char *) * map->height);
	
	for (i = 0; i < map->height; i++) {
	
		map->mapPptr[i] = (char *) malloc (sizeof(char) * (map->width+1));
	} 
	
	for (i = 0; i < map->height; i++) {
			
		fscanf (f, "\n%[^\n]", map->mapPptr[i]);
		map->mapPptr[i][map->width] = '\0';	
	}
	
	fclose(f);
}

void lookingFor (Wizard_t *wizard, int which, Map_t *map) {
	
	int i, j, k = 0;
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			if (map->mapPptr[i][j] == wizard->type) {
				
				k++;
				
				if (k == which) {
					
					wizard->x = (float)j;
					wizard->y = (float)i;
					
					break;
				}
			}
		}
		
		if (k == which) break;
	}	
}

void lookingForMonster (Monster_t *monster, int which, Map_t *map){
	
	int i, j, k = 0;
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			if (map->mapPptr[i][j] == monster->type) {
				
				k++;
				
				if (k == which) {
					
					monster->x = j;
					monster->y = i;
					
					break;
				}
			}
		}
		
		if (k == which) break;
	}	
}

int hotDogCounter(Map_t *map) {
	
	int i, j, qtd = 0;
	
	for(i = 0; i < map->height; i++){
		for(j = 0; j < map->width; j++){
			
			if(map->mapPptr[i][j] == ' '){
				qtd++;
			}
			
		}
	}
	return qtd;
}

void freeze (Map_t *map, int blizzard) {
	
	int temp = 0, auxHeight, auxWidth;
	int y = 0, x = 0, i , j;
	
	srand(time(0));
	
	if (blizzard >= 1) {
	
		while (temp <= 4) {
			
			do {
			
				y = rand() % ((map->height) - 1);
				x = rand() % ((map->width) - 1); 
				
				if (y == 0) y = 1;
				if (x == 0) x = 1; 
			
			} while (map->mapPptr[y][x] != ' ');
			
					
			if (map->mapPptr[y][x] == ' ') {
							
			for (i = y - 1; i < (y + 2);  i++) {
				
				for (j = x - 1; j < (x + 2); j++) {
					
					if (map->mapPptr[i][j] == ' ') map->mapPptr[i][j] = 'I';
				}
			}
			
		  	temp++;
			  	
			} else temp--;			
		}
		
	} else return;
}

void deFreeze (Map_t *map, Wizard_t *wizard, int fireDuration, int finalTime) {
	
	float x = 0, y = 0;
	int coordX[3], coordY[3], i, j;
	
	if (fireDuration != 0) {
		
		switch (wizard->direction) {
			
			case 0:
					
				x = (wizard->x + (map->imageSize) - (map->outOfLimitsX));
				y = (wizard->y - (map->outOfLimitsY));
				
				coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
				coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
				coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
				coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
				coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
				coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
				for (i = 0; i < 3; i++) {
					
					for (j = 0; j < 3; j++) {
						
						fireDuration = finalTime;
						
						if (map->mapPptr[coordY[i]][coordX[j]] == 'I' && fireDuration % 30 == 0) map->mapPptr[coordY[i]][coordX[j]] = 'H';
						else if (map->mapPptr[coordY[i]][coordX[j]] == 'H' && fireDuration % 29 == 0) map->mapPptr[coordY[i]][coordX[j]] = ' ';
					} 
				}
				
				break;
				
			case 1:
				
				x = (wizard->x - (map->imageSize + map->outOfLimitsX));
				y = (wizard->y - (map->outOfLimitsY));
				
				coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
				coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
				coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
				coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
				coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
				coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
				for (i = 0; i < 3; i++) {
					
					for (j = 0; j < 3; j++) {
						
						fireDuration = finalTime;
					
						if (map->mapPptr[coordY[i]][coordX[j]] == 'I' && fireDuration % 30 == 0) map->mapPptr[coordY[i]][coordX[j]] = 'H';
						else if (map->mapPptr[coordY[i]][coordX[j]] == 'H' && fireDuration % 29 == 0) map->mapPptr[coordY[i]][coordX[j]] = ' ';
					} 
				}
				
				break;
				
			case 2:
				
				x = (wizard->x - (map->outOfLimitsX));
				y = (wizard->y + (map->imageSize) - (map->outOfLimitsY));
				
				coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
				coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
				coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
				coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
				coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
				coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
				for (i = 0; i < 3; i++) {
					
					for (j = 0; j < 3; j++) {
						
						fireDuration = finalTime;
					
						if (map->mapPptr[coordY[i]][coordX[j]] == 'I' && fireDuration % 30 == 0) map->mapPptr[coordY[i]][coordX[j]] = 'H';
						else if (map->mapPptr[coordY[i]][coordX[j]] == 'H' && fireDuration % 29 == 0) map->mapPptr[coordY[i]][coordX[j]] = ' ';
					} 
				}
				
				break;
				
			case 3: 
			
				x = (wizard->x - (map->outOfLimitsX));
				y = (wizard->y - (map->imageSize + map->outOfLimitsY));
				
				coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
				coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
				coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
				coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
				coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
				coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
				for (i = 0; i < 3; i++) {
					
					for (j = 0; j < 3; j++) {
						
						fireDuration = finalTime;
					
						if (map->mapPptr[coordY[i]][coordX[j]] == 'I' && fireDuration % 30 == 0) map->mapPptr[coordY[i]][coordX[j]] = 'H';
						else if (map->mapPptr[coordY[i]][coordX[j]] == 'H' && fireDuration % 29 == 0) map->mapPptr[coordY[i]][coordX[j]] = ' ';
					} 
				}
				
				break;	
		}
	}
}

int deFreezeCrystal (Map_t *map, Wizard_t *wizard, int fireDuration, int finalTime, int *which) {
	float x = 0, y = 0;
	int coordX[3], coordY[3], i, j,k, correct = 0, minY, maxY, minX, maxX, whichNum;
	char crystalType;
	static int preFinalTime;

	if(finalTime > preFinalTime) fireDuration = finalTime;
	else fireDuration = 1;
	
	switch(wizard->direction){
		
		case 0:
			x = (wizard->x + (map->imageSize) - (map->outOfLimitsX));
			y = (wizard->y - (map->outOfLimitsY));
				
			coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
			coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
			coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
			coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
			coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
			coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
			break;
			
		case 1:
			x = (wizard->x - (map->imageSize + map->outOfLimitsX));
			y = (wizard->y - (map->outOfLimitsY));
				
			coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
			coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
			coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
			coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
			coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
			coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
			break;
			
		case 2:
			
			x = (wizard->x - (map->outOfLimitsX));
			y = (wizard->y + (map->imageSize) - (map->outOfLimitsY));
				
			coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
			coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
			coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
							
			coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
			coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
			coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
	
			break;
			
		case 3:
			
			x = (wizard->x - (map->outOfLimitsX));
			y = (wizard->y - (map->imageSize + map->outOfLimitsY));
				
			coordX[0] = ((x - (map->imageSize / 8)) / map->imageSize);
			coordX[1] = ((x + (map->imageSize / 2)) / map->imageSize);
			coordX[2] = ((x + map->imageSize + (map->imageSize / 8)) / map->imageSize); 
				
			coordY[0] = ((y - (map->imageSize / 8)) / map->imageSize);
			coordY[1] = ((y + (map->imageSize / 2)) / map->imageSize);
			coordY[2] = (((y + map->imageSize) + (map->imageSize / 8)) / map->imageSize);
				
			break;	
	}
	
	if(fireDuration % 30 == 0){
		if(coordX[1] < 25 && coordY[1] < 12){
			minY = 2;
			maxY = 5;
			minX = 3;
			maxX = 6;
			whichNum = 0;
		}else if(coordX[1] > 25 && coordY[1] < 12){
			minY = 2;
			maxY = 5;
			minX = 44;
			maxX = 47;
			whichNum = 1;
		}else if(coordX[1] < 25 && coordY[1] > 12){
			minY = 21;
			maxY = 24;
			minX = 3;
			maxX = 6;
			whichNum = 2;
		}else if(coordX[1] > 25 && coordY[1] > 12){
			minY = 21;
			maxY = 24;
			minX = 44;
			maxX = 47;
			whichNum = 3;
		}
			
		for(i = minY; i <= maxY; i++){
			for(j = minX; j <= maxX; j++){
				for(k = 0; k < 3; k++){
						
					if(coordY[k] == i && coordX[k] == j){
						correct = 1;
						break;
					}
				}
				if(correct == 1) break;
				}
			if(correct == 1) break;
		}
			
		if(correct == 1){
				
			for(i = minY; i <= maxY; i++){
				for(j = minX; j <= maxX; j++){
					crystalType = (map->mapPptr[i][j] - 1);
						
					if(crystalType >= 49) map->mapPptr[i][j] = crystalType;
						
				}
					
			}
				
			if(which[whichNum] >= 1) which[whichNum] -= 1; 
			preFinalTime = finalTime;
			return 1;
		}	
	}
	preFinalTime = finalTime;
	
	return 0;
}

void spawnLightning(Map_t *map, int *score, int *missing) {
	
	int x, y;
	int spawn = 0;
	
	srand (time(0));
	
	while (spawn == 0) {
		
		x = rand () % map->width;
		y = rand () % map->height;
		
		if (map->mapPptr[y][x] == ' ') {
			
			map->mapPptr[y][x] = '+';
			
			(*score)++;
			(*missing)--;
			
			spawn = 1;
			
		} else if (map->mapPptr[y][x] == '-') {
			
			map->mapPptr[y][x] = '+';
			
			(*score)++;
			(*missing)--;
			
			spawn = 1;	
		}
	}
}

int gameOver (Wizard_t *wizard, Map_t *map, float xo, float yo, int imageSizeX, int imageSizeY) {

	float xD, yD, xO, yO, xd, yd;
	
	xd = wizard->x + 3;
	yd = wizard->y + 3;
	
	xD = (wizard->x + map->imageSize) - 3;
	yD = (wizard->y + map->imageSize) - 3;
		
	xO = xo + imageSizeX;
	yO = yo + imageSizeY;
		
		if ((((xo < xd) && (xO > xd)) || ((xo < xD) && (xO > xD))) && 
			(((yo < yd) && (yO > yd)) || ((yo < yD) && (yO > yD)))) {
				
			if(wizard->type == 'D') return 1;	
		}
	
	return 0;
}

void freeMap (Map_t *map) {
	
	int i;
	
	for (i = 0; i < map->height; i++) {
		
		free(map->mapPptr[i]);
	}
	
	free(map->mapPptr);
}
