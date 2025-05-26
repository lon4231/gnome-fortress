#ifndef _GFR_WINDOW_INCLUDED_
#define _GFR_WINDOW_INCLUDED_

#include <headers.h>

#define RENDER_TEXTURE_W (800)
#define RENDER_TEXTURE_H (600)
#define RENDER_TEXTURE_HW (RENDER_TEXTURE_W/2)
#define RENDER_TEXTURE_HH (RENDER_TEXTURE_H/2)
#define RENDER_TEXTURE_ASPECT_RATIO (float)((float)RENDER_TEXTURE_W / (float)RENDER_TEXTURE_H)
struct window_hnd_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect render_texture_rect;
    SDL_Texture *render_texture;

    TTF_Font*font;

    uint32_t window_w;
    uint32_t window_h;

    bool running;
};

extern window_hnd_t window_hnd;

void init_window_hnd();
void handle_window(SDL_Event *event);

#endif