#ifndef _GAME_DEFINED_
#define _GAME_DEFINED_

#include <headers.h>
#include <game_server.h>
#include <ui.h>

struct game_state_t
{
    game_server_state_t remote_state;


    SDL_Rect board_rect;
    SDL_Texture *board_texture;

    uint32_t text_wall_size;
    SDL_Texture**text_wall_texture;
    const char**text_wall;
};

struct ui_layer_t
{
    bool button_active;
    SDL_Rect ready_button_trect;
    ui_button_t ready_button;
};

extern game_state_t game_state;
extern ui_layer_t ui_layer;

void game_init();
void game_update();

void update_text_wall();

#endif