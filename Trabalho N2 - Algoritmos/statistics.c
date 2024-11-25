#include <stdio.h>
#include <stdlib.h>
#include "menuScreens.h"

void saveData (int lives, int finalTime, int phase) {
	
	FILE *data;
	
	char pathPhase[] = "phase .txt";
	pathPhase[5] = (phase + 48);
	
	data = fopen(pathPhase, "w");
	
	if (data == NULL) {
		
		printf ("Erro ao abrir arquivo");
	}

	fprintf (data, "Time: %d\n", finalTime);
	fprintf(data, "Lives: %d", lives);

	fclose (data);
}

void changeStatisticsMap(){
	int i,j, nums[4], lives, minutes, seconds, aux;
	FILE *data;
	int y, x;
	float finalTime;
	
	for(i = 0; i < 5; i++){
		char pathPhase[] = "phase .txt";
		pathPhase[5] = (i + 49);
		
		data = fopen(pathPhase, "r");
		
		fseek(data, 5, SEEK_SET);
		
		fscanf(data, " %f", &finalTime);
		
		aux = finalTime;
		aux = aux/10;
		finalTime = aux;
		
		finalTime = finalTime/60;
		
		minutes = finalTime;
		seconds = ((finalTime - minutes) * 100);
		
		if(minutes != 0) nums[3] = (minutes/10) % 10;
		nums[2] = minutes % 10;
		
		seconds = (seconds * 60) / 100;
		
		if(seconds != 0) nums[1] = (seconds/10) % 10;
		nums[0] = seconds % 10;
		
		if (finalTime == 0) {
			
			for (j = 0; j < 4; j++) {
				
				nums[j] = 0;
			}
		}
		
		fseek(data, -1, SEEK_END);
		
		fscanf(data, "%d", &lives);
		
		y = 7 + (i * 4);
		
		if ((statisticsMap.mapPptr[y][43] - 48) < lives) {
			
			statisticsMap.mapPptr[y][21] = (nums[3] + 48);
			statisticsMap.mapPptr[y][23] = (nums[2] + 48);
			statisticsMap.mapPptr[y][27] = (nums[1] + 48);
			statisticsMap.mapPptr[y][29] = (nums[0] + 48);
			statisticsMap.mapPptr[y][43] = (lives + 48);
		}
		
		fclose(data);
	}	
}
