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
#include "statistics.h"

//Organizar pasta de assets
//Hitbox do dragao
//Mudar Musica de cada fase
//Mudar ogro
//Criar pasta statistics
//colocar "pill" na função de spawnar lightning
//Fazer imagens cinzas
//Juntar imagens do blizzard
//Cutscene da luta final e Gaguinho no final
//parar musica quando parar o tempo;

int main(int argc, char *argv[]) {
	const Uint8 *state;
    int  selection = 1;
    float firstTime, secondTime, aux = 0;
    int finalTime, preTime = 1, phases, print, option = 0, i;
    SDL_Event event;
	
	initSDL();
	
	initSound();
	
	makeTextures();
	
	makeScreenTextures();

    firstTime = clock();
    
    Map_t map_aux;
    

    while(1){
    	phases = 1;
    	
    	changeStatisticsMap();
    
   		for(i = 0; i < 5; i++){
    	
    		if(statisticsMap.mapPptr[(i*4) + 7][43] != '0') phases++;
    		if(phases >= 5) phases = 5;
		}	
		
		if(option == 0){
			
			playSound(0);
			
		    while(1){
		        secondTime = clock();
		        aux = secondTime - firstTime;
		        aux /= CLOCKS_PER_SEC;
		        finalTime = aux * 10;
		
		        if(print == 0) mainScreen(selection);
		        else mainScreen(5);
		
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
		
		            if(selection < 4) selection++;
		            mainScreen(selection);
		
		        }
		
		        if(state[SDL_SCANCODE_RETURN] && selection == 1){
		            break;
		        }
		        
		        if(state[SDL_SCANCODE_RETURN] && selection == 3){
		        	
		        	while(1){
		        		
		        		statisticsScreen();
		        		
						while(SDL_PollEvent(&event));
		
		        		state = SDL_GetKeyboardState(NULL);
		        		
		        		if(state[SDL_SCANCODE_ESCAPE]) break;
					}
		        	
				}
		
		        if(state[SDL_SCANCODE_RETURN] && selection == 4){
		            exit(1);
		        }
		    }
		    
		    option++;
		}
	    
	    Sleep(100);
	    
	    firstTime = clock();
	    selection = 1;
	    
	    while(1){
	    	secondTime = clock();
	        aux = secondTime - firstTime;
	        aux /= CLOCKS_PER_SEC;
	        finalTime = aux * 10;
	
	        if(print == 0) choosePhaseScreen(phases, selection);
	        else choosePhaseScreen(phases, 0);
	
	        if(finalTime > (preTime + 4)){
	            preTime = finalTime;
	
	            if(print == 0) print = 1;
	            else print = 0;
	        }
	
	        while(SDL_PollEvent(&event));
	
	        state = SDL_GetKeyboardState(NULL);
	
	        if(state[SDL_SCANCODE_W]){
	
	            selection = 1;
	             if(phases == 1 && selection > 1) selection = 1;
	        	if(phases == 2 && selection > 2) selection = 2;
	        	if(phases == 3 && selection > 3) selection = 3;
	        	if(phases == 4 && selection > 4) selection = 4;
	            choosePhaseScreen(phases, selection);
	
	        }
	
	        if(state[SDL_SCANCODE_S]  && phases >= 4){
	
	            selection = 4;
	            if(phases == 1 && selection > 1) selection = 1;
	        	if(phases == 2 && selection > 2) selection = 2;
	        	if(phases == 3 && selection > 3) selection = 3;
	        	if(phases == 4 && selection > 4) selection = 4;
	            choosePhaseScreen(phases, selection);
	
	        }
	        
	        if(state[SDL_SCANCODE_A]){
	
	            if(selection > 1) selection--;
	            if(phases == 1 && selection > 1) selection = 1;
	        	if(phases == 2 && selection > 2) selection = 2;
	        	if(phases == 3 && selection > 3) selection = 3;
	        	if(phases == 4 && selection > 4) selection = 4;
	            choosePhaseScreen(phases, selection);
	
	        }
	
	        if(state[SDL_SCANCODE_D]){
	
	            if(selection < 5) selection++;
	            if(phases == 1 && selection > 1) selection = 1;
	        	if(phases == 2 && selection > 2) selection = 2;
	        	if(phases == 3 && selection > 3) selection = 3;
	        	if(phases == 4 && selection > 4) selection = 4;
	            choosePhaseScreen(phases, selection);
	
	        }
	
	        if(state[SDL_SCANCODE_RETURN]){
	        
	            break;
	        }
	        
	        if (state[SDL_SCANCODE_ESCAPE]) {
	        	
	        	option = 0;
	        	break;
			}
		}
		
		Mix_HaltMusic();
		
		if(selection == 1 && option != 0){
			option = -1;
			
			while(option == -1){
				option = phase1();
			}
			selection++;
		}
		
		if(selection == 2 && option != 0){
			option = -1;
			
			while(option == -1){
				option = phase2();
			}
			selection++;
			
		}
		
		if(selection == 3 && option != 0){
			option = -1;
			
			while(option == -1){
				option = phase3();
			}
			selection++;
		
		}
		
		if(selection == 4 && option != 0){
			option = -1;
		
			while(option == -1){
				option = phase4();
			}
			selection++;
		
		}
		
		if(selection == 5 && option != 0){
			option = -1;
			
			while(option == -1){
				option = finalPhase();
			}
			selection++;
			
		}
	}
	
	freeSDL ();
	
	return 0;
}
