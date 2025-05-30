#ifndef _MAIN_MENU_DEFINED_
#define _MAIN_MENU_DEFINED_

#include <headers.h>

struct game_init_data_t
{
    char *port;
    char *ip;
    char *p_name;
};

extern game_init_data_t game_init_data;

void main_menu_init();
void main_menu_update();

void play_menu_update();
void play_menu_init();

#endif