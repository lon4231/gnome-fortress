#ifndef _GFR_RENDER_INCLUDED_
#define _GFR_RENDER_INCLUDED_

#include "headers.h"
#include "window.h"
#include "mwdt.h"
#include "cards.h"

struct render_hnd_t
{
SDL_Texture*cards[CARD_COUNT];
SDL_Texture*map_terrain;


};

extern render_hnd_t render_hnd;

void init_renderer();
void handle_render();




#endif