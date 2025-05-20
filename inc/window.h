#pragma once

#include "headers.h"

struct window_hnd_t
{
SDL_Window*window;
SDL_Renderer*renderer;

uint32_t window_w;
uint32_t window_h;

bool running;


}__attribute__((packed));

extern window_hnd_t window_hnd;



void init_window_hnd();
void handle_window(SDL_Event*event);
