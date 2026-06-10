#pragma once


#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>

int InitGraphics(void **appstate, int argc, char *argv[]);
int InputEvent(void *appstate, SDL_Event *event);
int RenderFrame(void *appstate);
int CleanGraphics(void *appstate, SDL_AppResult result);

extern SDL_Renderer* renderer;
extern SDL_Window* window;

typedef struct {
    uint16_t x;
    uint16_t y;
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Pixel;
typedef void (RenderCallback)(SDL_Renderer *Renderer);
RenderCallback* AddRenderCallback(RenderCallback callback);

#endif