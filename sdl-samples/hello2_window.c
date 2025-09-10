/**
* hello2_window.c - Initializes SDL and creates a window
*/

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// speed in pixels/second
#define SCROLL_SPEED 300

int main(void) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    // SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    SDL_Window * win = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (!win) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    if(!rend) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // The above call to SDL_LogSetAllPriority() should make SDL print which backend was used when
	// creating the renderer, but do it ourselves anyway.
	SDL_RendererInfo info;
	SDL_GetRendererInfo(rend, &info);
	printf("Renderer backend: %s\n", info.name);

    SDL_Event event;
    int isRunning = 1;

    // load the image into memory using SDL_image library function
    SDL_Surface * surface = IMG_Load("resources/hello.png");

    if (!surface) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    if (!tex) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // position the sprite at the bottom center of the window
    // origin is the top left corner, positive y is down
    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    // require float resolution for y position
    float y_pos = WINDOW_HEIGHT;

    int running = 1;
    // animation loop
    while (running && dest.y >= -dest.h) {
        // handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // clear the window
        SDL_RenderClear(rend);

        // set the y position in the struct
        dest.y = (int) y_pos;

        // draw the image to the window
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

        // update sprite position
        y_pos -= (float) SCROLL_SPEED / 60;

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }


    // clear the window
    SDL_RenderClear(rend);

    // draw the image to the window
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);

    // wait for 5 seconds
    SDL_Delay(5000);

    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
