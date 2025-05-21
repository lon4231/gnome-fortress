#include "headers.h"
#include "window.h"
#include "render.h"
#include "mwdt.h"

inline void init_libs()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    SDLNet_Init();
}

inline void handle_events()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
    }
}



int main()
{
    init_libs();
    init_window_hnd();


    terrain_buffer_t buffer=gen_terrain(1024,1024);
    
    SDL_Surface*terrain_surface=SDL_CreateRGBSurfaceWithFormat(0,1024,1024,32,SDL_PIXELFORMAT_RGBA8888);

    for(uint32_t i=0;i<1024*1024;++i)
    {
    ((uint32_t*)terrain_surface->pixels)[i]=((uint8_t)(buffer.terrain[i]*255))<<16 | 0xFF;
    }

    render_hnd.map_terrain=SDL_CreateTextureFromSurface(window_hnd.renderer,terrain_surface);

    init_renderer();

    while (window_hnd.running)
    {
        handle_events();

        handle_render();
    }
    return 0;
}