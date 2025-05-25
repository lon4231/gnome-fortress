#include "window.h"

window_hnd_t window_hnd;

void init_window_hnd()
{
    window_hnd.window = SDL_CreateWindow("gnome fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RENDER_TEXTURE_W, RENDER_TEXTURE_H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window_hnd.renderer = SDL_CreateRenderer(window_hnd.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    window_hnd.window_w = RENDER_TEXTURE_W;
    window_hnd.window_h = RENDER_TEXTURE_H;
    window_hnd.running = true;

    window_hnd.render_texture_rect = {0, 0, RENDER_TEXTURE_W, RENDER_TEXTURE_H};
    window_hnd.render_texture = SDL_CreateTexture(window_hnd.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
}

void update_render_texture_rect()
{
    float window_aspect_ratio = (float)window_hnd.window_w / window_hnd.window_h;
    if (window_aspect_ratio > RENDER_TEXTURE_ASPECT_RATIO)
    {
        int new_w = (int)(window_hnd.window_h * RENDER_TEXTURE_ASPECT_RATIO);
        int new_h = window_hnd.window_h;
        int offset_x = (window_hnd.window_w - new_w) / 2;
        int offset_y = 0;
        window_hnd.render_texture_rect = {offset_x, offset_y, new_w, new_h};
    }
    else
    {
        int new_w = window_hnd.window_w;
        int new_h = (int)(window_hnd.window_w / RENDER_TEXTURE_ASPECT_RATIO);
        int offset_x = 0;
        int offset_y = (window_hnd.window_h - new_h) / 2;
        window_hnd.render_texture_rect = {offset_x, offset_y, new_w, new_h};
    }
}

void handle_window(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        window_hnd.running = false;
        break;

    case SDL_WINDOWEVENT:
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            window_hnd.window_w = event->window.data1;
            window_hnd.window_h = event->window.data2;
            update_render_texture_rect();
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}