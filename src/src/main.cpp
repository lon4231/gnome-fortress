#include <headers.h>
#include <window.h>

#include <main_menu.h>

typedef void (*scene_fn_handle_t)();

static scene_fn_handle_t scene_fn_handle;

inline void init_libs()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    SDLNet_Init();
}

int main()
{
    init_libs();
    init_window_hnd();

    main_menu_init();

    scene_fn_handle = main_menu_update;

    while (window_hnd.running)
    {
        scene_fn_handle();
    }
    return 0;
}