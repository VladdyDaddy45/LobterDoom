#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "graphics/graphics.h"
#include "utils/funclist.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *icon;

int Width, Height;

FuncList Pipeline;

int InitGraphics(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Lobter Doom", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    icon = SDL_LoadPNG("assets/icon.png");
    if (!icon) {
        SDL_Log("Icon loading failed: %s", SDL_GetError());
    } else {
        SDL_SetWindowIcon(window, icon);
    }

    Pipeline = FuncList_new();
    SDL_GetWindowSize(window, &Width, &Height);

    printf("App Initialized Successfully\n");
    return SDL_APP_CONTINUE;
}

int InputEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_W) {
            printf("yo button was pressed fr\n");
        }
    }
    if (event->type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_GetWindowSize(window, &Width, &Height);
        SDL_SetRenderLogicalPresentation(renderer, Width, Height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    return SDL_APP_CONTINUE;
}

int RenderFrame(void *appstate)
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    // Calling the render pipeline
    for (int i = 0; i < Pipeline.size; i++) { Pipeline.arr[i](); }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

int CleanGraphics(void *appstate, SDL_AppResult result)
{
    SDL_DestroySurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PushPipeline(AnyFunc callback)
{   
    printf("Pushing to pipeline\n");
    FuncList_add(&Pipeline, callback);
}