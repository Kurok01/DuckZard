#include <stdio.h>
#include <stdlib.h>

void saveData (int lives, int finalTime, int phase) {
	
	FILE *data;
	
	data = fopen("Statistics.txt", "w+");
	
	if (data == NULL) {
		
		printf ("Erro ao abrir arquivo");
	}
	
	fprintf (data, "Phase: %d\n", phase);
	fprintf (data, "Time %d\n", finalTime);
	fprintf(data, "Lives: %d\n", lives);
	
	fclose (data);
}
