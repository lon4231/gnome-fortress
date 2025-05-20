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

    while (window_hnd.running)
    {
        handle_events();

        handle_render();
    }
    return 0;
}