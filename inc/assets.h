#ifndef _ASSETS_HEADER_DEFINED_
#define _ASSETS_HEADER_DEFINED_

#include <headers.h>

struct runtime_assets_t
{
    SDL_Texture *game_bg;
    SDL_Texture *menu_bg;
    SDL_Texture *title_texture;
    SDL_Texture *buttons_texture;
    SDL_Texture *ip_text_input_texture;
    SDL_Texture *name_text_input_texture;

    SDL_Texture *board_tiles;

    Mix_Music* songloop0;
    Mix_Music* songloop1;
};

extern runtime_assets_t runtime_assets;

void load_assets();

#endif