#include <fmt/core.h>
#include <SDL2/SDL.h>
#include <math.h>
#define PI 3.1415926535

float px = 100, py = 120,
pdx, pdy, pa; // Player Position
bool isRunning;
SDL_Window *window;
SDL_Renderer *renderer;
int SCREEN_WIDTH = 800 ,SCREEN_HEIGHT = 512;
SDL_Event event;
SDL_Rect fillRect;
const int playerSize = 10;
const int mapX = 8, mapY = 8, mapSize = 64;
int map[mapX][mapY] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
};

void initWindow(const char *title, int xPos, int yPos, int width, int height, int shown) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    if(SDL_Init(SDL_INIT_VIDEO) == 0) {
        fmt::print("Subsystems initialized\n");

        window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
        if(window) fmt::print("Window Created\n");

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            fmt::print("Renderer Created\n");
        }

        isRunning = true;
    }
    else isRunning = false;
}

void initPlayer(int x, int y, int w, int h) {
    fillRect  = { x, y, w, h };

    pdx = 5*cos(pa); pdy = 5*sin(pa);
}

void movePlayer() {
    if(event.key.keysym.sym == SDLK_s) {
        px -= pdx;
        py -= pdy;

        fillRect.x = px;
        fillRect.y = py;
    } else if(event.key.keysym.sym == SDLK_w) {
        fillRect.y -= playerSize/2;
        px += pdx;
        py += pdy;

        fillRect.x = px;
        fillRect.y = py;
    } else if(event.key.keysym.sym == SDLK_d) {
        pa+=0.1; if(pa>2*PI) { pa -= 2*PI; } pdx = 5*cos(pa); pdy = 5*sin(pa);
    } else if(event.key.keysym.sym == SDLK_a) {
        pa-=0.1; if(pa<0) { pa += 2*PI; } pdx = 5*cos(pa); pdy = 5*sin(pa);
    }
}

void renderPlayer() {
    SDL_SetRenderDrawColor( renderer, 255, 5, 5, 255 );
    SDL_RenderFillRect( renderer, &fillRect );

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, fillRect.x, fillRect.y, fillRect.x+pdx*5, fillRect.y+pdy*5);
}

void renderBackground() {
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderClear(renderer);
}

void polling() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}



void renderMap() {
    for(int x=0; x<mapX; x++) {
        for(int y=0; y<mapY; y++) {
            SDL_Rect tile = { x*mapSize, y*mapSize, mapSize-2, mapSize-2};
            if(map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else SDL_SetRenderDrawColor(renderer, 1, 1, 1, 255);

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void exitProgram() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    fmt::print("Game Cleaned\n");
}

int main(int argc, const char *argv[]) {
    initWindow("Ray Caster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, true);
    initPlayer(px, py, playerSize, playerSize);

    while(isRunning) {
        /* Event Polling */
        polling();

        // Update Position
        movePlayer();

        /* Rendering */
        renderBackground();
        renderMap();
        renderPlayer();

        SDL_RenderPresent(renderer);
        event.key.keysym.sym = SDLK_0;
    }

    /* Exiting Program */
    exitProgram();
    return 0;
}