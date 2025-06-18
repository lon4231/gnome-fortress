#ifndef _GAME_DEFINED_
#define _GAME_DEFINED_

#include <headers.h>

struct game_state_t
{
float player_y;
float player_sy;

};

extern game_state_t game_state;

void game_init();
void game_update();

#endif