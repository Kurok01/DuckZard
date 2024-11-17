#include <stdio.h>
#include "interface.h"
#include "structs.h"
#include "actions.h"
#include "mapFunctions.h"
#include "phase.h"

//Arrumar parede, Comer hots do dogs, portal do mago implacavel, Criar projeteis, Criar movimento dos ogros, Colocar musica
//Organizar pasta de assets
//Cutscene da luta final e Gaguinho no final


int main(int argc, char *argv[]) {
	
	initSDL();
	
	makeTextures();
	
	void initSound ();
	
	phase1();
	
	return 0;
}
