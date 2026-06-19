#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "graphics/graphics.h"
#include "utils/fpsCounter.h"
#include "types.h"

//const double PI = 3.141592653589793;
extern double PI;

// -------------------------- game stuf

int maxsteps = 200;
float step = 0.1f;
int fidelity = 80;
double columnHeight = 1;
int fov = 60;

double speed = 4;

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

typedef struct {
    bool W;
    bool A;
    bool S;
    bool D;
} Pressed;

Pressed pressed = {0,0,0,0};

Player plr;

i8 map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,0,0,1,1,1},
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
    pos->x += dist * sin(dir);
    pos->y += dist * cos(dir);
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

v2 cast(v2 pos, double angle, i8 map[10][10]) {

    for (i16 i = 0; i < maxsteps; i++) {
        move_forward(&pos, angle, step);
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

void input(SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_W:
                pressed.W = true;
                break;
            case SDL_SCANCODE_A:
                pressed.A = true;
                break;
            case SDL_SCANCODE_S:
                pressed.S = true;
                break;
            case SDL_SCANCODE_D:
                pressed.D = true;
                break;
            case SDL_SCANCODE_V:
                printf("FPS: %.5lf, DeltaTime: %.5lf\n", 1.0/DeltaTime, DeltaTime);
                break;
        }
    }
    if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_W:
                pressed.W = false;
                break;
            case SDL_SCANCODE_A:
                pressed.A = false;
                break;
            case SDL_SCANCODE_S:
                pressed.S = false;
                break;
            case SDL_SCANCODE_D:
                pressed.D = false;
                break;
        }
    }
}

void movement() {
    if (pressed.W == true) { move_forward(&(plr.pos),rad(plr.rot),DeltaTime *  speed); }
    if (pressed.S == true) { move_forward(&(plr.pos),rad(plr.rot),DeltaTime * -speed); }
    if (pressed.A == true) { plr.rot -= DeltaTime * 90; }
    if (pressed.D == true) { plr.rot += DeltaTime * 90; }

    if (plr.rot < 0) {
        plr.rot += 360;
    }
    if (plr.rot > 360) {
        plr.rot -= 360;
    }
}

void draw() {
    fidelity = (double)Width;
    float space = (double)Width / fidelity;
    double incr = (double)fov/(double)fidelity;

    for (int i = 0; i < fidelity; i++) {
        v2 ray = cast(plr.pos, rad((plr.rot - fov/2) + (i*incr)), map);
        double dist = distance(ray, plr.pos);

        int h = (int)((columnHeight * (double)Height)/dist);
        drawRect(
            vec2(i * space,(Height/2) + (h/2)),
            vec2((i+1)*space,(Height/2) - (h/2)),
            (Color){255,0,0,255}
        );
    }
}

void start() {
    Player player = {
        {4.0,4.0},
        0
    };

    plr = player;
    v2 pos = cast(plr.pos, 0, map);
    //printf("X: %.5lf, Y: %.5lf\n",pos.x,pos.y);
    //printf("Dist: %lf\n", distance(plr.pos,pos));
    PushPipeline(draw);
    PushPipeline(fpscounter);
    PushPipeline(movement);
    AddInputEvent(input);
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