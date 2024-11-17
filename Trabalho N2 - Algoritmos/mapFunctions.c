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

void lookingFor (Role_t *character, int which, Map_t *map) {
	
	int i, j, k = 0;
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			if (map->mapPptr[i][j] == character->type) {
				
				k++;
				
				if (k == which) {
					
					character->x = (float)j;
					character->y = (float)i;
					
					break;
				}
			}
		}
		
		if (k == which) break;
	}	
}

void lookingForOgre(Ogre_t *character, int which, Map_t *map){
	
	int i, j, k = 0;
	
	for (i = 0; i < map->height; i++) {
		
		for (j = 0; j < map->width; j++) {
			
			if (map->mapPptr[i][j] == character->type) {
				
				k++;
				
				if (k == which) {
					
					character->x = (float)j;
					character->y = (float)i;
					
					break;
				}
			}
		}
		
		if (k == which) break;
	}	
}

int hotDogCounter(Map_t *map){
	int i,j, qtd = 0;
	
	for(i = 0; i < map->height; i++){
		for(j = 0; j < map->width; j++){
			
			if(map->mapPptr[i][j] == ' '){
				qtd++;
			}
			
		}
	}
	return qtd;
}

int gameOver (Role_t *wizard, float x, float y, int imageSizeX, int imageSizeY) {

	float xD, yD, xO, yO;

	xD = wizard->x + imageSizeX;
	yD = wizard->y + imageSizeY;
		
	xO = x + imageSizeX;
	yO = y + imageSizeY;
		
		if ((((x < wizard->x) && (xO > wizard->x)) || ((x < xD) && (xO > xD))) && 
			(((y < wizard->y) && (yO > wizard->y)) || ((y < yD) && (yO > yD)))) {
					
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
