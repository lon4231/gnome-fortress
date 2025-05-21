#include "render.h"

render_hnd_t render_hnd; 

void init_renderer()
{

}

void handle_render()
{
SDL_SetRenderDrawColor(window_hnd.renderer,0,0,0,255);
SDL_RenderClear(window_hnd.renderer);

SDL_RenderCopyEx(window_hnd.renderer,render_hnd.map_terrain,NULL,NULL,0,NULL,SDL_FLIP_NONE);

SDL_RenderPresent(window_hnd.renderer);
}