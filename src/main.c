#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "graphics/graphics.h"
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f64 rot;
} Player;

Player plr;

void draw() {
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderPoint(renderer,(float)Width/2.0f,(float)((int)Height >> 1));
}

// Surrogate 'Main' function
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    printf("Starting program...\n");
    SDL_AppResult r = InitGraphics(appstate,argc,argv);

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