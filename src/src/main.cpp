#include <headers.h>
#include <window.h>

#include <keyboard.h>
#include <main.h>
#include <main_menu.h>
#include <server/server.h>

scene_fn_handle_t scene_fn_handle;

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
    init_keyboard();

    
    main_menu_init();

    scene_fn_handle = main_menu_update;

    while (window_hnd.running)
    {
        if (scene_fn_handle != nullptr)
        {
            scene_fn_handle();
        }
    }
    return 0;
}