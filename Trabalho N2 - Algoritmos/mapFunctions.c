#include <stdio.h>
#include <stdlib.h>
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

int hotDogCounter(Map_t *map){
	
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
				
			return 1;	
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
