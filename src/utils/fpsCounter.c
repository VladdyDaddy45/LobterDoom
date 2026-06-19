#include <math.h>
#include <stdio.h>

#include "graphics/graphics.h"
#include "utils/fpsCounter.h"
#include "SDL3/SDL.h"
#include "types.h"

// this is shit.
i8 (font[4])[5][5] = {
    { // F
        {1,1,1,1,1},
        {1,0,0,0,0},
        {1,1,1,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
    },
    { // P
        {1,1,1,1,0},
        {1,0,0,0,1},
        {1,1,1,1,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
    },
    { // S
        {0,1,1,1,1},
        {1,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,1},
        {1,1,1,1,0},
    },
    { // :
        {0,0,0,0,0},
        {1,0,0,0,0},
        {0,0,0,0,0},
        {1,0,0,0,0},
        {0,0,0,0,0},
    },
};

i8 nums[10][5][5] = {
    { // 0
        {0,1,1,1,0},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {0,1,1,1,0}
    },
    { // 1
        {0,1,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1}
    },
    { // 2
        {1,1,1,1,0},
        {0,0,0,0,1},
        {0,1,1,1,0},
        {1,0,0,0,0},
        {1,1,1,1,1}
    },
    { // 3
        {1,1,1,1,0},
        {0,0,0,0,1},
        {1,1,1,1,0},
        {1,0,0,0,1},
        {1,1,1,1,0}
    },
    { // 4
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {0,0,0,0,1},
        {0,0,0,0,1}
    },
    { // 5
        {0,1,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,0,1,0,0},
        {1,1,1,1,0}
    },
    { // 6
        {0,1,1,1,1},
        {1,0,0,0,0},
        {1,1,1,1,0},
        {1,0,0,0,1},
        {0,1,1,1,0}
    },
    { // 7
        {1,1,1,1,1},
        {0,0,0,1,0},
        {0,0,1,0,0},
        {0,1,0,0,0},
        {1,0,0,0,0}
    },
    { // 8
        {0,1,1,1,0},
        {1,0,0,0,1},
        {0,1,1,1,0},
        {1,0,0,0,1},
        {0,1,1,1,0}
    },
    { // 9
        {0,1,1,1,1},
        {1,0,0,0,1},
        {0,1,1,1,1},
        {0,0,0,0,1},
        {0,0,0,0,1}
    },
};

// this is absolute garbage. i don't care though. mainly because it's not used.
i8 (*getgrid(char idx))[5][5] {
    switch (idx) {
        // text
        case 'F':
            return &(font[0]);
            break;
        case 'P':
            return &(font[1]);
            break;
        case 'S':
            return &(font[2]);
            break;
        case ':':
            return &(font[3]);
            break;
        // nums
        case '0':
            return &(nums[0]);
            break;
        case '1':
            return &(nums[1]);
            break;
        case '2':
            return &(nums[2]);
            break;
        case '3':
            return &(nums[3]);
            break;
        case '4':
            return &(nums[4]);
            break;
        case '5':
            return &(nums[5]);
            break;
        case '6':
            return &(nums[6]);
            break;
        case '7':
            return &(nums[7]);
            break;
        case '8':
            return &(nums[8]);
            break;
        case '9':
            return &(nums[9]);
            break;
    }
}


int scale = 3;

void drawgrid(i8 grid[5][5], int scale, int X, int Y) {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (grid[y][x] == 0) {continue;}
            SDL_FRect rect = {
                X + (x * scale),
                Y + (y * scale),
                scale,
                scale,
            };

            SDL_RenderRect(renderer,&rect);
        }
    }
}

void fpscounter() 
{
    double framerate = 1.0/DeltaTime;
    int fps = (int)(framerate);
    int deci = 0;
    int n = fps;

    for (int i = 0; i < 5 && n != 0; i++) {
        n /= 10;
        deci++;
    }

    //printf("FPS: %d, digits: %d\n",fps, deci);

    i8 digits[deci];

    int burner = fps;
    for (int i = 0; i < deci && burner != 0; i++) {
        digits[(deci-1) - i] = burner % 10;
        burner /= 10;
    }

    for (int i = 0; i < 4 + deci; i++) {
        SDL_SetRenderDrawColor(renderer,255,255,255,200);
        if (i < 4) {
            drawgrid(font[i], scale, 10 + (i * scale * 6), 10);
        } else if(i >= 4) {
            drawgrid(nums[digits[i-4]], scale, 10 + (i * scale * 6), 10);
        }
    }
}