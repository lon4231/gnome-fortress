#ifndef _GNOME_STATE_OF_THY_ART_
#define _GNOME_STATE_OF_THY_ART_

#include <headers.h>

#define BOARD_WIDTH 512
#define BOARD_HEIGHT 512

struct game_player_state_t
{
    char name[8];
    uint32_t gnome_count;
};

struct game_state_header_t
{
};

#endif