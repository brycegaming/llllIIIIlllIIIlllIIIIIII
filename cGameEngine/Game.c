#include "include/Game.h"
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
#include "include/Panel.h"

/**
 * interpolates finds the average between two values skewed by float t [0-1]
 * */
float linearlyInterpolate(float v0, float v1, float t);

int g_rows = 4;
int g_cols = 10;
float spacing = 3.0f;
float speed = 10;

float meteorSpeed = 5;
float meteorHeight = 2;

Instance* game;

GameObject** groundObjects;
GameObject** obstacleObjects;

GameObject* character;
Model* characterModel;

Model* meteorModel;
Model* fenceModel;
Model* finishModel;

Model* groundModel;
Model* lampModel;
Model* barModel;

int* gameRunning;

float groundHeight = -7.0f;
float characterHeight = -4.9f;

int numBlocks = 5;
MapBlock blocks[5];

//how close you have to be to an obstacle to be considered colliding with it
float collisionRadius = 2.0f;

/**
 * loads a level and sets current variables accordingly
 * */
static void loadLevel(const char* levelPath, MapBlock* blocks, int blockCount);

/**
 * removes the level from the loaded state
 */
static void unloadLevel();

/**
 * terminates the player's game
 * unloads the level and places them back in the menu
 * */
static void die();

Panel* mainMenu;
Panel* creditMenu;
Panel* levelSelectMenu;

int inMainMenu = 1;

static int mainMenuExit(){
    *gameRunning = 0;
    while(InstanceRemovePanel(game));
    return 0;
}

static int loadCreditMenu(){
    InstanceAddPanel(game, creditMenu);
    return 0;
}

static int removeMenu(){
    InstanceRemovePanel(game);
    return 0;
}

static int loadLevelSelectMenu(){
    InstanceAddPanel(game, levelSelectMenu);
    return 0;
}

static int loadHardLevel(){
    //remove all menus
    while(InstanceRemovePanel(game));
    loadLevel("./res/levels/demoLevels/HARD.bmp", blocks, numBlocks);
    loadCharacter();
    game->paused = 0;
    setCamera();

    inMainMenu = 0;

    return 0;
}

static int loadMediumLevel(){
    //remove all menus
    while(InstanceRemovePanel(game));
    loadLevel("./res/levels/demoLevels/MEDIUM.bmp", blocks, numBlocks);
    loadCharacter();
    game->paused = 0;

    inMainMenu = 0;

    return 0;
}

static int loadTutorialLevel(){
    //remove all menus
    while(InstanceRemovePanel(game));
    loadLevel("./res/levels/demoLevels/TUTORIAL.bmp", blocks, numBlocks);
    loadCharacter();
    game->paused = 0;
    setCamera();

    inMainMenu = 0;

    return 0;
}

static int loadDemonLevel(){
    //remove all menus
    while(InstanceRemovePanel(game));
    loadLevel("./res/levels/demoLevels/DEMON.bmp", blocks, numBlocks);
    loadCharacter();
    game->paused = 0;
    setCamera();

    inMainMenu = 0;

    return 0;
}

void setCamera(){
    game->camera.position.y = 4;
    game->camera.position.x = 0;
}

void loadCharacter(){
    //load the character
    character = NcursesCreateGameObject(characterModel, "charcter", NULL, game);
    character->transform.position.x = 0;
    character->transform.position.y = characterHeight;
    character->transform.position.z = -11;
    character->transform.rotation.y = DEG2RAD(180);
}

void start(int* running, Instance** instance){
    gameRunning = running;
    game = *instance;

    groundModel = ModelLoad("./res/models/ground.obj");
    lampModel = ModelLoad("./res/models/lamp.obj");
    barModel = ModelLoad("./res/models/bar.obj");
    characterModel = ModelLoad("./res/models/testObj.obj");
    meteorModel = ModelLoad("./res/models/meteor.obj");
    fenceModel = ModelLoad("./res/models/fence.obj");
    finishModel = ModelLoad("./res/models/finish.obj");

    int block = 0;
    blocks[block++] = MapBlockCreate(NULL, 0, 0, 0, 0, 1, 1, 1, 0, 0, 3, 1);
    blocks[block++] = MapBlockCreate(lampModel, 0, 255, 0, 1.5f, .7f, .5f, .7f, 0, 1, 2, 0);
    blocks[block++] = MapBlockCreate(barModel, 0, 255, 255, 1.5f, 1.5f, 1.5f, 1, DEG2RAD(-90), 1, 4, 1);
    blocks[block++] = MapBlockCreate(barModel, 0, 0, 255, 1.5f, 1.5f, 1.5f, 1, DEG2RAD(90), 1, 4, 1);
    blocks[block++] = MapBlockCreate(fenceModel, 255, 0, 255, 1.3f, 1.5f, 1.5f, 1.2, DEG2RAD(-90), 1, 1, 0);

    //set the light
    game->camera.lightPos.x = 0;
    game->camera.lightPos.y = 50;
    game->camera.lightPos.z = -10;
    game->camera.rotation.y = 0.5;

    setCamera();

    //create the panel
    mainMenu = PanelCreate("Welcome To DASH!~Press d to select~a menu item", COLS/2-15, 5, 30, 15, 3);
    mainMenu->textOffsetX = 5;
    mainMenu->textOffsetY = 2;
    mainMenu->optionFunctions[0] = loadLevelSelectMenu;
    mainMenu->optionFunctions[1] = loadCreditMenu;
    mainMenu->optionFunctions[2] = mainMenuExit;
    strcpy(mainMenu->options, "*    Level Select~*    Credits~*    Exit :(");
    InstanceAddPanel(game, mainMenu);

    levelSelectMenu = PanelCreate("Please select your level", COLS/2-15, 10, 30, 15, 5);
    levelSelectMenu->textOffsetX = 5;
    levelSelectMenu->textOffsetY = 2;
    levelSelectMenu->optionFunctions[0] = loadTutorialLevel;
    levelSelectMenu->optionFunctions[1] = loadMediumLevel;
    levelSelectMenu->optionFunctions[2] = loadHardLevel;
    levelSelectMenu->optionFunctions[3] = loadDemonLevel;
    levelSelectMenu->optionFunctions[4] = removeMenu;
    strcpy(levelSelectMenu->options, "*    EASY~*    MEDIUM~*    HARD~*    DEMON~*    Back");

    creditMenu = PanelCreate("By Bryce Young", COLS/2-15, 10, 30, 15, 1);
    creditMenu->textOffsetX = 5;
    creditMenu->textOffsetY = 2;
    creditMenu->optionFunctions[0] = removeMenu;
    strcpy(creditMenu->options, "*    Back");

    game->paused = 1;

    MainLoop(running, game, GameUpdate);

    //free
    ModelFree(groundModel);
    ModelFree(lampModel);
    ModelFree(characterModel);
    ModelFree(fenceModel);
    ModelFree(finishModel);
    ModelFree(meteorModel);
    ModelFree(barModel);

    PanelFree(creditMenu);
    PanelFree(mainMenu);
    PanelFree(levelSelectMenu);
}

float nearRender = -12.5f;
float farRender = -80;
float angularVelocity = 2.0f;
float angularAcceleration = 5.0f;
float linearAcceleration = -20.0f;

int inMotion = 0;
float targetLocation = 0;
float startLocation = 0;
float moveTime = .17f;
float currMoveTime = 0.0f;

int jumping = 0;

char GameUpdate(float delta, int* running){
    if(inMainMenu){
        setCamera();
        jumping = 0;
        currMoveTime = 0;
        inMotion = 0;
        return 0;
    }

    nodelay(stdscr, 1);
    char input = getch();

    //input
    if(!inMotion && input == CHAR_a){
        inMotion = -1;
        currMoveTime = 0.0f;

        startLocation = character->transform.position.x;
        targetLocation = character->transform.position.x - spacing;
    }
    if(!inMotion && input == CHAR_d){
        inMotion = 1;
        currMoveTime = 0.0f;

        startLocation = character->transform.position.x;
        targetLocation = character->transform.position.x + spacing;
    }

    if(character->transform.position.y < characterHeight){
        character->transform.position.y = characterHeight;
        character->physics.velocity.y = 0;
        character->physics.acceleration.y = 0;
        jumping = 0;
    }

    if(!jumping && !inMotion && input == ' '){
        character->physics.velocity.y = 10;
        character->physics.acceleration.y = -22;
        jumping = 1;
    }

    if(inMotion){
        //spacing / moveTime is the movement speed in d/s
        //game->camera.position.x += inMotion * (spacing / moveTime) * delta * .7f;
        //game->camera.position.x = character->transform.position.x;
        //character->transform.position.x += inMotion * (spacing / moveTime) * delta;
        character->transform.position.x = linearlyInterpolate(startLocation, targetLocation, ((float)currMoveTime / moveTime));
        game->camera.position.x = linearlyInterpolate(startLocation, targetLocation, ((float)currMoveTime / moveTime));

        //rotate character based on motion
        if(inMotion == -1){
            character->transform.rotation.y = (inMotion * PI + (PI / 5.0f));
        }
        else if(inMotion == 1){
            character->transform.rotation.y = (inMotion * PI - (PI / 5.0f));
        }

        currMoveTime += delta;

        if(currMoveTime > moveTime){
            inMotion = 0;
            character->transform.position.x = linearlyInterpolate(startLocation, targetLocation, 1.0f);
        }
    }
    else{
        character->transform.rotation.y = PI;
    }

    //update the ground objects
    //also test if you are colliding with the terrain
    int collidingWithTerrain = jumping;

    for(int i = 0; i < g_rows * g_cols; i++){
        if(groundObjects[i] == NULL){
            continue;
        }

        if(groundObjects[i]->transform.position.z > nearRender){
            groundObjects[i]->physics.angularVelocity.x = angularVelocity;
            groundObjects[i]->physics.angularAcceleration.x = angularAcceleration;
            groundObjects[i]->physics.acceleration.y = linearAcceleration;
        }

        if(groundObjects[i]->transform.position.z > nearRender + 9){
            groundObjects[i]->rendering = 0;
        }
        else if(groundObjects[i]->transform.position.z < farRender){
            groundObjects[i]->rendering = 0;
        }
        else{
            groundObjects[i]->rendering = 1;
        }

        if(Vec3Distance(&groundObjects[i]->transform.position, &character->transform.position) < 3.3f){
            collidingWithTerrain = 1;
        }
    }

    if(!collidingWithTerrain){
        die();
        return 0;
    }

    //move the obstacle objects properly
    for(int i = 0; i < g_rows * g_cols; i++){
        if(obstacleObjects[i] == NULL){
            continue;
        }

        if(obstacleObjects[i]->transform.position.z > nearRender){
            if(strcmp("meteor", obstacleObjects[i]->tag)){
                obstacleObjects[i]->physics.angularVelocity.x = angularVelocity;
                obstacleObjects[i]->physics.angularAcceleration.x = angularAcceleration;
                obstacleObjects[i]->physics.acceleration.y = linearAcceleration;
            }
        }

        if(obstacleObjects[i]->transform.position.z > nearRender + 9){
            obstacleObjects[i]->rendering = 0;
        }
        else if(obstacleObjects[i]->transform.position.z < farRender){
            obstacleObjects[i]->rendering = 0;
        }
        else{
            obstacleObjects[i]->rendering = 1;
        }

        float ty = obstacleObjects[i]->transform.position.y;
        obstacleObjects[i]->transform.position.y = character->transform.position.y;

        if(Vec3Distance(&obstacleObjects[i]->transform.position, &character->transform.position) < collisionRadius){
            //*running = 0;
            die();
        }

        obstacleObjects[i]->transform.position.y = ty;
    }

    return input;
}

static void die(){
    unloadLevel();
    inMainMenu = 1;
    InstanceAddPanel(game, mainMenu);
    game->paused = 1;
}

static void unloadLevel(){
    free(groundObjects);
    free(obstacleObjects);
    NcursesClearGameObjects(game);
}

static void loadLevel(const char* levelPath, MapBlock* blocks, int blockCount){
    //load the map
    BMPData* level = BMPLoad(levelPath, game->colors, NUM_COLORS);
    g_rows = level->width;
    g_cols = level->height;

    float xPos = 0.0f, yPos = groundHeight, zPos = -10.0f;
    float maxZ = 0;
    xPos = floor(-(g_rows * spacing)/2.0f);

    //allocate object arrays
    groundObjects = (GameObject**)malloc(sizeof(GameObject*) * g_rows * g_cols);
    obstacleObjects = (GameObject**)malloc(sizeof(GameObject*) * g_rows * g_cols);

    for(int i = 0; i < g_rows; i++){
        for(int j = 0; j < g_cols; j++){
            obstacleObjects[g_cols * i + j] = NULL;

            //get the color of the pixel at this point in the map
            BMPPixel* pixel = BMPGetPixel(level, i, j);
            float red, green, blue;
            red = pixel->r;
            green = pixel->g;
            blue = pixel->b;

            int addGround = 1;

            if(red == 255 && blue == 0){
                if(green == 0 || green == 100){
                    GameObject* obj = NcursesCreateGameObject(meteorModel, "meteor", NULL, game);

                    obj->transform.scale.x = 1.5f;
                    obj->transform.scale.y = 1.5f;
                    obj->transform.scale.z = 1.5f;

                    obj->transform.position.x = xPos;
                    obj->transform.position.y = yPos + meteorHeight;

                    float distance = zPos * meteorSpeed + ((spacing * 3) * (meteorSpeed - 1));
                    obj->transform.position.z = distance;

                    obj->transform.rotation.y = DEG2RAD(90);

                    obj->physics.velocity.z = speed * meteorSpeed;

                    obj->texture = 0;

                    obstacleObjects[g_cols * i + j] = obj;

                    if(green == 100){
                        addGround = 0;
                    }
                }
            }

            for(int k = 0; k < blockCount; k++){
                MapBlock b = blocks[k];

                if(b.r == red && b.g == green && b.b == blue){
                    if(b.model == NULL){
                    }
                    else{
                        GameObject* obj = NcursesCreateGameObject(b.model, "obstacle", NULL, game);

                        obj->transform.scale.x = b.scalex;
                        obj->transform.scale.y = b.scaley;
                        obj->transform.scale.z = b.scalez;

                        obj->transform.position.x = xPos;
                        obj->transform.position.y = yPos + b.height;
                        obj->transform.position.z = zPos;

                        obj->transform.rotation.y = b.roty;

                        obj->physics.velocity.z = speed;
                        obj->texture = b.texture;
                        obj->cullBackFaces = b.cull;

                        obstacleObjects[g_cols * i + j] = obj;
                    }

                    addGround = b.onGround;

                    break;
                }
            }

            if(addGround){
                GameObject* obj = NcursesCreateGameObject(groundModel, "ground", NULL, game);
                obj->transform.scale.x = 2.0f;
                obj->transform.scale.y = 3.0f;
                obj->transform.scale.z = 2.0f;

                obj->transform.position.x = xPos;
                obj->transform.position.y = yPos;
                obj->transform.position.z = zPos;

                obj->transform.rotation.y = DEG2RAD(RAND_IN_RANGE(0, 100));

                obj->physics.velocity.z = speed;

                obj->texture = 3;
                obj->cullBackFaces = 1;

                groundObjects[g_cols * i + j] = obj;
            }
            else{
                groundObjects[g_cols * i + j] = NULL;
            }

            zPos -= spacing;
        }

        maxZ = zPos;
        xPos += spacing;
        zPos = -10.0f;
    }

    //add the finish line
    GameObject* finish = NcursesCreateGameObject(finishModel, "ground", NULL, game);
    finish->transform.position.z = maxZ - spacing;
    finish->transform.position.x = -1;
    finish->transform.position.y = groundHeight;

    finish->transform.scale.z = 1.0f;
    finish->transform.scale.x = 8.0f;
    finish->transform.scale.y = 8.0f;

    finish->physics.velocity.z = speed;

    BMPFree(level);
}

MapBlock MapBlockCreate(Model* model, float r, float g, float b, float height, float scalex, float scaley, float scalez, float roty, int onGround, int texture, int cull){
    MapBlock ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;
    ret.model = model;
    ret.onGround = onGround;
    ret.scalex = scalex;
    ret.scaley = scaley;
    ret.scalez = scalez;
    ret.texture = texture;
    ret.height = height;
    ret.roty = roty;
    ret.cull = cull;

    return ret;
}

float linearlyInterpolate(float v1, float v2, float t){
    return (1.0f - t) * v1 + t * v2;
}


