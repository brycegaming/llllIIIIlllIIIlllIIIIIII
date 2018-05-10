//main.c

#include "include/defs.h"
#include "include/Vector2.h"
#include "include/GameObject.h"
#include "include/Ncurses.h"
#include "include/GenericSet.h"
#include "include/Vertex.h"
#include "include/Matrix22.h"
#include "include/Matrix44.h"
#include "include/Vector3.h"
#include "include/BMPLoader.h"
#include "include/Color.h"
#include "include/Texture.h"
#include "include/Time.h"
#include "include/SplashScreen.h"
#include "include/Game.h"

int running = 1;

int main(int argc, char** argv){
    //clear the console initially
    clearConsole();
    srand(time(0));

    Instance* game;

    //create an instance of the current engine by calling start
    NcursesInit(&game, 100, 80);

    TextureLoadFromBMP(0, BMPLoad("./res/textures/meteor.bmp", game->colors, NUM_COLORS));
    TextureLoadFromBMP(1, BMPLoad("./res/textures/RED.bmp", game->colors, NUM_COLORS));
    TextureLoadFromBMP(2, BMPLoad("./res/textures/lampTexture.bmp", game->colors, NUM_COLORS));
    TextureLoadFromBMP(3, BMPLoad("./res/textures/groundPlateTexture.bmp", game->colors, NUM_COLORS));
    TextureLoadFromBMP(4, BMPLoad("./res/textures/barTexture.bmp", game->colors, NUM_COLORS));

    //output the splash screen
    running = splashScreen(&running, &game);
    //running = 1;

    start(&running, &game);

    //tell threads to stop running
    running = 0;

    //close ncurses to make sure the console works after ending the program
    NcursesDeInit(game);

    return 0;
}

