#include "render.h"

void init_renderer()
{

}

void handle_render()
{
SDL_SetRenderDrawColor(window_hnd.renderer,0,0,0,255);
SDL_RenderClear(window_hnd.renderer);



SDL_RenderPresent(window_hnd.renderer);
}