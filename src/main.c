#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "graphics/graphics.h"
#include "utils/funclist.h"

typedef struct {
    double x;
    double y;
    double rot;
} Player;

Player plr;

void func() {
    printf("working\n");
}

void test() {
    printf("working but cooler\n");
}

// Surrogate 'Main' function
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    printf("Starting program\n");
    FuncList list = FuncList_new();
    FuncList_add(&list, (void*)func);
    FuncList_add(&list, (void*)test);
    
    function method = (function)list.arr[0];
    method();

    int thing = 12;
    printf("thingamajig: %d\n",&thing);

    printf("App Initializing...\n");
    return InitGraphics(appstate,argc,argv);
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
    //printf("Rendering\n");

    /*
    int width, height;
    SDL_GetWindowSize(window,&width,&height);
    printf(&width);
    printf(", ");
    printf(&height);
    printf("\n");
    SDL_RenderPoint(renderer,width-50,height-50);
    */
    SDL_RenderPoint(renderer,60.0f,50.0f);
    return r;
}

// Quitting the app
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    printf("Quit: %d\n", result);
    CleanGraphics(appstate,result); 
}