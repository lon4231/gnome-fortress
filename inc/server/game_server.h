#ifndef _IMAGINE_HOSTING_A_GAME_LIKE_WTF_DEFINED_
#define _IMAGINE_HOSTING_A_GAME_LIKE_WTF_DEFINED_

#include <headers.h>
#include <net_routines.h>

#define BOARD_W 32
#define BOARD_H 32
#define MAX_CLIENTS 32

struct game_server_client_t
{
    char name[8];
    uint32_t poblation;
};

struct game_server_state_t
{

    uint8_t board[BOARD_W * BOARD_H];
    uint8_t disp_board[BOARD_W * BOARD_H];

    uint8_t client_count;
    game_server_client_t clients[MAX_CLIENTS];
};

void update_game_state(game_server_state_t*state);

#endif