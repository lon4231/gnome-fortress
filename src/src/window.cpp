#include "window.h"

window_hnd_t window_hnd;

void init_window_hnd()
{
    window_hnd.window = SDL_CreateWindow("gnome fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window_hnd.renderer = SDL_CreateRenderer(window_hnd.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    window_hnd.window_w = 800;
    window_hnd.window_h = 600;
    window_hnd.running = true;
}

void handle_window(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        window_hnd.running = false;
        break;

    default:
        break;
    }
}