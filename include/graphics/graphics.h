#pragma once


#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>

int InitGraphics(void **appstate, int argc, char *argv[]);
int InputEvent(void *appstate, SDL_Event *event);
int RenderFrame(void *appstate);
int CleanGraphics(void *appstate, SDL_AppResult result);

#endif