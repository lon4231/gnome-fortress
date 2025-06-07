#ifndef _RNDR_ROUTINES_DEFINED_
#define _RNDR_ROUTINES_DEFINED_

#include <headers.h>
#include <window.h>

inline SDL_Texture *routines_load_texture(const char *path)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(window_hnd.renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

inline SDL_Surface *routines_load_surface(const char *path)
{
    return IMG_Load(path);
}

inline SDL_Texture *routines_render_text_texture(const char *text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(window_hnd.font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window_hnd.renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}


inline void routines_draw_window()
{
    SDL_SetRenderDrawColor(window_hnd.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window_hnd.renderer);
    SDL_RenderCopy(window_hnd.renderer, window_hnd.render_texture, NULL, &window_hnd.render_texture_rect);
    SDL_RenderPresent(window_hnd.renderer);
}

#endif