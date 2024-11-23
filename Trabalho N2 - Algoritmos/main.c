#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "menuScreens.h"
#include "interface.h"
#include "structs.h"
#include "actions.h"
#include "mapFunctions.h"
#include "phase.h"

//Organizar pasta de assets
//Hitbox do dragao
//Mudar Musica de cada fase
//Cutscene da luta final e Gaguinho no final


int main(int argc, char *argv[]) {
	
	const Uint8 *state;
    int  selection = 1;
    float firstTime, secondTime, aux = 0;
    int finalTime, preTime = 1, print;
    SDL_Event event;
	
	initSDL();
	
	makeTextures();
	
	makeScreenTextures();

    firstTime = clock(); 

    /*while(1){
        secondTime = clock();
        aux = secondTime - firstTime;
        aux /= CLOCKS_PER_SEC;
        finalTime = aux * 10;

        if(print == 0) mainScreen(selection);
        else mainScreen(4);

        if(finalTime > (preTime + 4)){
            preTime = finalTime;

            if(print == 0) print = 1;
            else print = 0;
        }

        while(SDL_PollEvent(&event));

        state = SDL_GetKeyboardState(NULL);

        if(state[SDL_SCANCODE_W]){

            if(selection > 1) selection--;
            mainScreen(selection);

        }

        if(state[SDL_SCANCODE_S]){

            if(selection < 3) selection++;
            mainScreen(selection);

        }

        if(state[SDL_SCANCODE_RETURN] && selection == 1){
            break;
        }

        if(state[SDL_SCANCODE_RETURN] && selection == 3){
            exit(1);
        }
    }*/

    initSound();
	
    phase2();
	
	return 0;
}
