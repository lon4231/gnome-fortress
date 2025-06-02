#ifndef _GAME_DEFINED_
#define _GAME_DEFINED_

#include <headers.h>
#include <game_server.h>

struct game_state_t
{
    game_server_state_t remote_state;

    SDL_Rect board_rect;
    SDL_Texture *board_texture;
};

extern game_state_t game_state;

void game_init();
void game_update();

#endif