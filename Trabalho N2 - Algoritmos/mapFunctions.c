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
	static int coolDown[9];
	
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

void deFreezeCrystal (Map_t *map, Wizard_t *wizard, int fireDuration, int finalTime, int *which) {
	
	float x = 0, y = 0;
	int coordX[3], coordY[3], i, j, k, l, m;
	static int coolDown[9];
	char crystalType;
	
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
						
						for (m = 1; m <= 5; m++) {
						
						crystalType = (m + 48);
						
						if (map->mapPptr[coordY[i]][coordX[j]] == crystalType && fireDuration % 30 == 0) {
							
							for (k = coordY[i] - 5; k < coordY[i] + 6; k++) {
								
								for (l = coordX[j] - 5; l < coordX[j] + 6; l++) {
									
									if (k < 0 || k > 49) k = 0;
									
									if (l < 0 || l > 25) l = 0; 
									
									if (map->mapPptr[k][l] == crystalType) {
										
										if (k < 25 && l < 12) which[0] -= 1;
										if (k > 25 && l < 12) which[1] -= 1;
										if (k < 25 && l > 12) which[2] -= 1;
										if (k > 25 && l < 12) which[3] -= 1;
									
										map->mapPptr[k][l] = crystalType - 1;
										}
									}
								}
							}	
						}
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
						
						for (m = 1; m <= 5; m++) {
						
						crystalType = (m + 48);
						
						if (map->mapPptr[coordY[i]][coordX[j]] == crystalType && fireDuration % 30 == 0) {
							
							for (k = coordY[i] - 5; k < coordY[i] + 6; k++) {
								
								for (l = coordX[j] - 5; l < coordX[j] + 6; l++) {
									
									if (k < 0 || k > 49) k = 0;
									
									if (l < 0 || l > 25) l = 0; 
									
									if (map->mapPptr[k][l] == crystalType) {
										
										if (k < 25 && l < 12) which[0] -= 1;
										if (k > 25 && l < 12) which[1] -= 1;
										if (k < 25 && l > 12) which[2] -= 1;
										if (k > 25 && l < 12) which[3] -= 1;
									
										map->mapPptr[k][l] = crystalType - 1;
										}
									}
								}
							}	
						}
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
					
						for (m = 1; m <= 5; m++) {
						
						crystalType = (m + 48);
						
						if (map->mapPptr[coordY[i]][coordX[j]] == crystalType && fireDuration % 30 == 0) {
							
							for (k = coordY[i] - 5; k < coordY[i] + 6; k++) {
								
								for (l = coordX[j] - 5; l < coordX[j] + 6; l++) {
									
									if (k < 0 || k > 49) k = 0;
									
									if (l < 0 || l > 25) l = 0; 
									
									if (map->mapPptr[k][l] == crystalType) {
										
										if (k < 25 && l < 12) which[0] -= 1;
										if (k > 25 && l < 12) which[1] -= 1;
										if (k < 25 && l > 12) which[2] -= 1;
										if (k > 25 && l < 12) which[3] -= 1;
									
										map->mapPptr[k][l] = crystalType - 1;
										}
									}
								}
							}	
						}
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
					
						for (m = 1; m <= 5; m++) {
						
						crystalType = (m + 48);
						
						if (map->mapPptr[coordY[i]][coordX[j]] == crystalType && fireDuration % 30 == 0) {
							
							for (k = coordY[i] - 5; k < coordY[i] + 6; k++) {
								
								for (l = coordX[j] - 5; l < coordX[j] + 6; l++) {
									
									if (k < 0 || k > 49) k = 0;
									
									if (l < 0 || l > 25) l = 0; 
									
									if (map->mapPptr[k][l] == crystalType) {
										
										if (k < 25 && l < 12) which[0] -= 1;
										if (k > 25 && l < 12) which[1] -= 1;
										if (k < 25 && l > 12) which[2] -= 1;
										if (k > 25 && l < 12) which[3] -= 1;
									
										map->mapPptr[k][l] = crystalType - 1;
										}
									}
								}
							}	
						}
					} 
				}
				
				break;	
		}
	}
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
