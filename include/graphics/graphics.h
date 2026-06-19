#pragma once


#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>
#include "utils/funclist.h"

int InitGraphics(void **appstate, int argc, char *argv[]);
int InputEvent(void *appstate, SDL_Event *event);
int RenderFrame(void *appstate);
int CleanGraphics(void *appstate, SDL_AppResult result);
void PushPipeline(AnyFunc callback);
void AddInputEvent(void (*callback)(SDL_Event *event));

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern int Width, Height;
extern double DeltaTime;

typedef struct {
    uint16_t x;
    uint16_t y;
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Pixel;

#endif