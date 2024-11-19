#include <stdio.h>
#include "interface.h"
#include "structs.h"
#include "actions.h"
#include "mapFunctions.h"
#include "phase.h"

//Hitbox do dragao, portal do mago implacavel, Criar movimento dos ogros
//Organizar pasta de assets
//Cutscene da luta final e Gaguinho no final


int main(int argc, char *argv[]) {
	initSDL();
	
	makeTextures();
	
	initSound ();
	
	phase3();
	
	return 0;
}
