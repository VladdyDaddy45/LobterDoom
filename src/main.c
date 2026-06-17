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

int maxsteps = 50;
float step = 0.1f;
int fidelity = 200;
int columnHeight = 1;

typedef struct {
    f32 x;
    f32 y;
} v2;

typedef struct {
    v2 pos;
    f64 rot;
} Player;

typedef struct {
    i8 r;
    i8 g;
    i8 b;
    i8 a;
} Color;

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

v2 vec2(float x, float y) {
    return (v2){x,y};
}

double distance(v2 a, v2 b) {
    return sqrt( pow( (b.x - a.x), 2) + pow( (b.y - a.y), 2) );
}

// use radians. degrees are for the weak.
void move_forward(v2* pos, double dir, double dist) {
    pos->x += dist * cos(dir);
    pos->y += dist * sin(dir);
}

double rad(double deg) {
    return deg * (PI/180);
}

void setcolor(Color color) {
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        color.a
    );
}

// You might get some weird bugs if the x/y of top_left is greater than x/y of bottom_right. idk, not testing that.
void drawRect(v2 top_left, v2 bottom_right, Color color) {
    setcolor(color);
    const SDL_FRect rect = {
        top_left.x, 
        top_left.y, 
        bottom_right.x - top_left.x, 
        bottom_right.y - top_left.y
    };

    SDL_RenderFillRect(renderer, &rect);
}

// degrees for angle.
v2 cast(Player* plr, double angle, i8 map[10][10]) {
    v2 pos = plr->pos;

    for (i16 i = 0; i < maxsteps; i++) {
        move_forward(&pos, rad(plr->rot-angle), step);
        if (
            pos.x > 10 || pos.x < 0 ||
            pos.y > 10 || pos.y < 0
        ) { return pos; }

        if (map[
             (int)round(pos.x)]
            [(int)round(pos.y)] == 1) {
            return pos;
        }
    }

    return pos;
}

void draw() {
    drawRect(
        vec2(0.0f,0.0f),
        vec2(Width/1.5,Height/1.5),
        (Color){255,0,0,255}
    );
}

void start() {
    Player player = {
        {4.0,4.0},
        0
    };

    plr = player;
    v2 pos = cast(&player, -5, map);
    printf("X: %.5lf, Y: %.5lf\n",pos.x,pos.y);

    PushPipeline(draw);
}

// --------------------------- main stuff

// Surrogate 'Main' function
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    printf("Starting program...\n");
    SDL_AppResult r = InitGraphics(appstate,argc,argv);

    start();

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
    return r;
}

// Quitting the app
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    printf("Quit: %d\n", result);
    CleanGraphics(appstate,result); 
}