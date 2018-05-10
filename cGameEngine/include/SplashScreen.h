#ifndef INCLUDE_SPLASH_SCREEN
#define INCLUDE_SPLASH_SCREEN

#include "Ncurses.h"

/**
 * displays the spash screen for the game
 * */
int splashScreen();

/**
 * input for the splash screen, includes the instructions and shit
 * */
char SpashScreenUpdate(float delta, int* running);

#endif
