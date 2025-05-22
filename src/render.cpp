#include "render.h"

const char*card_paths[CARD_COUNT]=
{
"assets/sprites/card_base.png",
};

render_hnd_t render_hnd; 

void init_renderer()
{
for(uint32_t i=0;i<CARD_COUNT;++i)
{
SDL_Surface*card_surface=IMG_Load(card_paths[i]);

render_hnd.cards[i]=SDL_CreateTextureFromSurface(window_hnd.renderer,card_surface);

SDL_FreeSurface(card_surface);
}
}


void handle_render()
{
SDL_SetRenderDrawColor(window_hnd.renderer,0,0,0,255);
SDL_RenderClear(window_hnd.renderer);

SDL_RenderCopyEx(window_hnd.renderer,render_hnd.map_terrain,NULL,NULL,0,NULL,SDL_FLIP_NONE);

SDL_RenderPresent(window_hnd.renderer);
}