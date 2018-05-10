#include "include/SplashScreen.h"
#include "include/defs.h"
#include "include/Vector2.h"
#include "include/GameObject.h"
#include "include/GenericSet.h"
#include "include/Vertex.h"
#include "include/Matrix22.h"
#include "include/Matrix44.h"
#include "include/Vector3.h"
#include "include/BMPLoader.h"
#include "include/Color.h"
#include "include/Texture.h"
#include "include/Time.h"

#define NO_MENU 0
#define MENU_INSTRUCTIONS 1
#define MENU_BACKSTORY 2

Model* meteor;
int numMeteors;
GameObject** meteors;
int splashLocationx, splashLocationy;
int inMenu = 0;

int cont = 0;
int* splashRunning = 0;

int splashScreen(int* running, Instance** instance){
    splashRunning = running;
    
    //set base location for splash
    splashLocationx = ((float)TERMINAL_COLS / 2.0f) - 22;
    splashLocationy = ((float)TERMINAL_LINES / 2.0f) - 10;
    
    meteor = ModelLoad("./res/models/meteor.obj");
    numMeteors = 40;
    meteors = (GameObject**)malloc(sizeof(GameObject) * numMeteors);

    for(int i = 0; i < numMeteors; i++){
        meteors[i] = NcursesCreateGameObject(meteor, "meteor", NULL, *instance);
        meteors[i]->texture = 0;

        meteors[i]->transform.position.z = RAND_IN_RANGE(-30, -20);
        meteors[i]->transform.position.y = RAND_IN_RANGE(20, 30);
        meteors[i]->transform.position.x = RAND_IN_RANGE(0, 30);

        //set angle of z
        float angle = RAND_IN_RANGE(30, 60);
        angle = DEG2RAD(angle);
        meteors[i]->transform.rotation.z = angle;

        float movementSpeed = (RAND_IN_RANGE(10, 25));
        meteors[i]->physics.velocity.x = -movementSpeed * cos(angle);
        meteors[i]->physics.velocity.y = -movementSpeed * sin(angle);

        float zAxisVelocity = (RAND_IN_RANGE(4, 8));
        meteors[i]->physics.velocity.z = zAxisVelocity;

        angle = atan(meteors[i]->physics.velocity.z / meteors[i]->physics.velocity.x);
        meteors[i]->transform.rotation.y = -angle;
    }

    MainLoop(running, *instance, SpashScreenUpdate);
    sleep_ms(100);

    ModelFree(meteor);
    free(meteors);

    //clear the list of game objects so new ones can be created in the main game
    NcursesClearGameObjects(*instance);
    return cont;
}

char SpashScreenUpdate(float delta, int* running){
    NcursesSetColorPair(WHITE);
    int lx = splashLocationx; 
    int ly = splashLocationy;

    //splash screen text: originally, I was going to load from an image file, but I cannot
    //trust my users to play on a high enough resolution, so I had to manually enter the 
    //text (Later this will be loaded from a text file
    mvprintw(ly++, lx, "8888888b.        d8888  .d8888b.  888    888");
    mvprintw(ly++, lx, "888  *Y88b      d88888 d88P  Y88b 888    888");
    mvprintw(ly++, lx, "888    888     d88P888 Y88b.      888    888");
    mvprintw(ly++, lx, "888    888    d88P 888  *Y888b.   8888888888");
    mvprintw(ly++, lx, "888    888   d88P  888     *Y88b. 888    888");
    mvprintw(ly++, lx, "888    888  d88P   888       *888 888    888");
    mvprintw(ly++, lx, "888  .d88P d8888888888 Y88b  d88P 888    888");
    mvprintw(ly++, lx, "8888888P* d88P     888  *Y8888P*  888    888");
    ly += 1;
    mvprintw(ly++, lx, "By: Bryce Young");
    mvprintw(ly++, lx, "CS 2060: Spring 2018");
    ly += 1;

    char input = 0;

    if(inMenu == NO_MENU){
        mvprintw(ly++, lx, "[I]nstructions");
        mvprintw(ly++, lx, "[P]lay");
        mvprintw(ly++, lx, "[B]ackstory");
        mvprintw(ly++, lx, "[E]xit");

        nodelay(stdscr, 1);
        input = getch();
            
        //normal menu options
        if(input == 'p'){
            *splashRunning = 0;
            cont = 1;
        }
        else if(input == 'b'){
            inMenu = MENU_BACKSTORY;
        }
        else if(input == 'i'){
            inMenu = MENU_INSTRUCTIONS;
        }
        else if(input == 'e'){
            *splashRunning = 0;
            cont = 0;
        }
    }
    else if(inMenu == MENU_INSTRUCTIONS){
        mvprintw(ly++, lx, "Instructions:");
        mvprintw(ly++, lx, "You move forward automatically");
        ly++;
        mvprintw(ly++, lx, "CONTROLS:");
        mvprintw(ly++, lx, "W: move left");
        mvprintw(ly++, lx, "D: move right");
        mvprintw(ly++, lx, "Space: jump");
        ly ++;
        mvprintw(ly++, lx, "GOAL:");
        mvprintw(ly++, lx, "Get to the end of the level without hitting any of the obstacles");
        ly++;
        mvprintw(ly++, lx, "-------PRESS ANY KEY TO RETURN------");

        nodelay(stdscr, 1);
        input = getch();

        //options for instructions as well
        if(input != -1){
            inMenu = NO_MENU;
        }
    }
    else if(inMenu == MENU_BACKSTORY){
        mvprintw(ly++, lx, "Backstory:");
        mvprintw(ly++, lx, "You are a captured soldier trapped in a military base deep in space.");
        mvprintw(ly++, lx, "While imprisoned, you overhear a sinister plot to dominate the world.");
        mvprintw(ly++, lx, "You must escape from your captors and warn the world before its too late.");
        ly++;
        mvprintw(ly++, lx, "-------PRESS ANY KEY TO RETURN------");

        nodelay(stdscr, 1);
        input = getch();

        if(input != -1){
            inMenu = NO_MENU;
        }
    }


    //spawn variables
    float minY = -20.0f;

    //TODO delta doesnt work on windows yet! so this should do for now
#ifdef WIN32
    //delta = .02f;
#endif
    
    for(int i = 0; i < numMeteors; i++){
        //update physics this will later be done in the main thread in the update physics section
        //additionally, it will be multiplied by a delta variable to maintain normalcy throughout varying framerates
        //respawn in necessary
        if(meteors[i]->transform.position.y < minY){
            meteors[i]->transform.position.z = RAND_IN_RANGE(-30, -20);
            meteors[i]->transform.position.y = RAND_IN_RANGE(20, 30);
            meteors[i]->transform.position.x = RAND_IN_RANGE(0, 30);

            //get z angle to random between 0  and 30
            float angle = RAND_IN_RANGE(30, 60);
            angle = DEG2RAD(angle);
            meteors[i]->transform.rotation.z = angle;

            //set velocities
            float movementSpeed = (RAND_IN_RANGE(15, 30));
            meteors[i]->physics.velocity.x = -movementSpeed * cos(angle);
            meteors[i]->physics.velocity.y = -movementSpeed * sin(angle);

            float zAxisVelocity = (RAND_IN_RANGE(4, 8));
            meteors[i]->physics.velocity.z = zAxisVelocity;

            angle = atan(meteors[i]->physics.velocity.z / meteors[i]->physics.velocity.x);
            meteors[i]->transform.rotation.y = -angle;
        }
    }

    //ouput the menu to the center of the screen
    return input;
}



