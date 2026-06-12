#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "graphics/graphics.h"
#include "types.h"

extern double PI;
// -------------------------- game stuf
typedef struct {
    f64 x;
    f64 y;
} v2;

typedef struct {
    v2 pos;
    f64 rot;
} Player;

Player plr;

i8 map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};

void start() {
    Player player = {
        {4.0,4.0},
        0
    };

    plr = player;

    for (int y = 0; y < sizeof(map) / sizeof(map[0]); y++) {
        for (int x = 0; x < sizeof(map[y]); x++) {
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}

void draw() {
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderPoint(renderer,(float)Width/2.0f,(float)Height/2.0f);
}

// --------------------------- main stuff

// Surrogate 'Main' function
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    printf("Starting program...\n");
    SDL_AppResult r = InitGraphics(appstate,argc,argv);

    start();
    PushPipeline(draw);

    return r;
}

// Input Events
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    SDL_AppResult r = InputEvent(appstate, event);
    return r;
}

// Frame Rendering
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_AppResult r = RenderFrame(appstate);
    SDL_RenderPoint(renderer,60.0f,50.0f);
    return r;
}

// Quitting the app
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    printf("Quit: %d\n", result);
    CleanGraphics(appstate,result); 
}