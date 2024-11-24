#ifndef MENUSCREEN_H
#define MENUSCREEN_H

void makeScreenTextures();

void mainScreen(int selection);

void choosePhaseScreen(int phases, int selection);

int winningScreen();

void printWinningScreen(int selection);

int gameOverScreen();

void printgameOverScreen(int selection);

void pauseScreen(int selection);

#endif
