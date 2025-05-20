#ifndef _GFR_RENDER_INCLUDED_
#define _GFR_RENDER_INCLUDED_

#include "headers.h"
#include "window.h"

struct render_hnd_t
{



SDL_Surface*map_terrain;


};

extern render_hnd_t render_hnd;

void init_renderer();
void handle_render();

#endif